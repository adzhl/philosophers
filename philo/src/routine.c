/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:00:50 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/26 13:19:11 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief (void *arg) is passed as the parameter and typecasted in the
 * function because pthread_create expects the prototype of a routine
 * function to be void *(*start_routine)(void*);
 * @return NULL because thread functions must return a void *
 */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (end_simulation(philo->data))
			break;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

/**
 * 1. Lock forks
 * 2. Lock mutex for eating
 * 3. Log activity
 * 4. Update last meal time
 * 5. Increment no of meals eaten
 * 6. Unlock mutex for eating
 * 7. Wait until reach assigned time to eat
 * 8. Unlock forks
 */
void	eating(t_philo *philo)
{
	if (end_simulation(philo->data))
		return;
	if (philo->data->no_of_philo == 1)
	{
		usleep_time(philo->data->time_to_die);
		return ;
	}
	take_fork(philo);
	pthread_mutex_lock(&philo->eat_mutex);
	log_activity("is eating", philo);
	philo->last_meal_time = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	usleep_time(philo->data->time_to_eat);
	put_fork(philo);
}

void	sleeping(t_philo *philo)
{
	if (end_simulation(philo->data))
		return;
	log_activity("is sleeping", philo);
	usleep_time(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	if (end_simulation(philo->data))
		return;
	log_activity("is thinking", philo);
}
