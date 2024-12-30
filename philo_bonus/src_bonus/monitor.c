/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:03:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 09:53:14 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

/**
 * @brief Simulation will stop when there is a philo death or
 * all philo had eaten enough
 */
void	monitor_routine(t_data *data)
{
	int	i;
	int	status;

	while (1)
	{
		i = -1;
		while (++i < data->no_of_philo)
		{
			if (philo_death(data, i))
			{
				sem_wait(data->sem->stop_simulation);
				log_activity("died", &data->philo[i]);
				stop_simulation(data);
				return ;
			}
			usleep(100);
		}
		if (eaten_enough(data))
			break ;
		usleep(500);
	}
	i = -1;
	while (++i < data->no_of_philo)
		waitpid(data->philo[i].pid, &status, 0);
}

int	philo_death(t_data *data, int i)
{
	long	current_time;
	long	time_since_eaten;
	int		is_dead;

	sem_wait(data->sem->meal_lock);
	current_time = get_timestamp();
	time_since_eaten = current_time - data->philo[i].last_meal_time;
	is_dead = (time_since_eaten >= data->time_to_die);
	sem_post(data->sem->meal_lock);
	return (is_dead);
}

/**
 * @brief iterate through every philosopher to check
 * if all of them had eaten enough
 */
int	eaten_enough(t_data *data)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = -1;
	while (++i < data->no_of_philo)
	{
		sem_wait(data->sem->meal_count_lock);
		if (data->philo[i].meals_eaten < data->must_eat_count)
		{
			sem_post(data->sem->meal_count_lock);
			return (0);
		}
		sem_post(data->sem->meal_count_lock);
	}
	return (1);
}

void	stop_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->no_of_philo)
		kill(data->philo[i].pid, SIGKILL);
	sem_post(data->sem->stop_simulation);
}
