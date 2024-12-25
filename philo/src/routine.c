/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:00:50 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/25 17:59:45 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_philo *philo)
{
	while (!philo->data->stop_simulation)
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
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
void	eat(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->eat_mutex);
	log_activity("is eating", philo->data);
	philo->last_meal_time = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	usleep_time(philo->data->time_to_eat);
	put_fork(philo);
}

void	sleep(t_philo *philo)
{
	log_activity("is sleeping", philo->data);
	usleep_time(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	log_activity("is thinking", philo->data);
}
