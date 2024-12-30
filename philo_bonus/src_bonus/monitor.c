/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:03:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 16:33:27 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	*eaten_enough(void *arg)
{
	t_data	*data;
	int		eaten;

	data = (t_data *)arg;
	eaten = 0;
	while (1)
	{
		sem_wait(data->sem->meal_count_lock);
		eaten++;
		if (eaten >= data->no_of_philo)
		{
			sem_wait(data->sem->stop_simulation);
			stop_simulation(data);
			sem_post(data->sem->stop_simulation);
			cleanup(data);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

void	*philo_death(void *ptr)
{
	t_philo	*philo;
	long	current_time;
	long	last_meal;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->sem->meal_lock);
		current_time = get_timestamp();
		last_meal = philo->last_meal_time;
		sem_post(philo->sem->meal_lock);
		sem_wait(philo->sem->stop_simulation);
		if (current_time - last_meal > philo->data->time_to_die)
		{
			log_activity("died", philo);
			sem_post(philo->sem->meal_lock);
			cleanup(philo->data);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->sem->stop_simulation);
	}
	return (NULL);
}

void	stop_simulation(t_data *data)
{
	int	i;

	i = -1;
	sem_wait(data->sem->pid_lock);
	while (++i < data->no_of_philo)
		kill(data->philo[i].pid, SIGKILL);
	sem_post(data->sem->pid_lock);
	sem_post(data->sem->stop_simulation);
}
