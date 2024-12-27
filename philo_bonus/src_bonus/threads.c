/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:23:58 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/27 14:55:53 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief pthread_create - creates threads
 * @note pthread_join - wait for threads to finish
 * @param newthread variable to hold thread ID
 * @param attr specify attributes (detached state, stack size etc.)
 * @param start_routine function that the thread will execute
 * @param arg argument to pass to the thread function
 */
void	create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	while (++i < data->no_of_philo)
		pthread_create(&data->philo[i].thread, NULL, philo_routine,
			&data->philo[i]);
	pthread_create(&monitor_thread, NULL, monitor_routine, data);
	i = -1;
	while (++i < data->no_of_philo)
		pthread_join(data->philo[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->no_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].eat_mutex);
		pthread_mutex_destroy(&data->philo[i].meal_count_mutex);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->stop_lock);
	free(data->forks);
	free(data->philo);
}
