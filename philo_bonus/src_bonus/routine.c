/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:00:50 by abinti-a          #+#    #+#             */
/*   Updated: 2025/01/03 17:03:28 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	pthread_t	death_checker;

	philo->last_meal_time = get_timestamp();
	if (philo->data->no_of_philo == 1)
		handle_single_philo(philo);
	pthread_create(&death_checker, NULL, philo_death, philo);
	pthread_detach(death_checker);
	if (philo->id % 2 == 0)
		usleep_time(10);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	eating(t_philo *philo)
{
	sem_wait(philo->sem->forks);
	log_activity("has taken a fork", philo);
	sem_wait(philo->sem->forks);
	log_activity("has taken a fork", philo);
	sem_wait(philo->sem->eating_lock);
	log_activity("is eating", philo);
	philo->last_meal_time = get_timestamp();
	philo->meals_eaten++;
	sem_post(philo->sem->eating_lock);
	if (philo->meals_eaten >= philo->data->must_eat_count)
		sem_post(philo->sem->meal_count_lock);
	usleep_time(philo->data->time_to_eat);
	sem_post(philo->sem->forks);
	sem_post(philo->sem->forks);
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
