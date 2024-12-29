/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:00:50 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/29 15:46:56 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	int stop_routine;

	while (1)
	{
		sem_wait(philo->data->stop_simulation);
		stop_routine = philo_death(philo->data, philo->id);
		sem_post(philo->data->stop_simulation);
		if (stop_routine)
			exit(0);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	eating(t_philo *philo)
{
	if (philo->data->no_of_philo == 1)
	{
		usleep_time(philo->data->time_to_die);
		return ;
	}
	sem_wait(philo->data->forks);
	log_activity("has taken a fork", philo);
	sem_wait(philo->data->forks);
	log_activity("has taken a fork", philo);
	log_activity("is eating", philo);
	philo->last_meal_time = get_timestamp();
	usleep_time(philo->data->time_to_eat);
	philo->meals_eaten++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	sleeping(t_philo *philo)
{
	log_activity("is sleeping", philo);
	usleep_time(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	log_activity("is thinking", philo);
}
