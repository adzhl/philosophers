/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:27:39 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 19:52:28 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Activity logging is a shared resource.
 * Therefore, it must be locked before using and unlocked after using
 */
void	log_activity(char *message, t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (end_simulation(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	timestamp = get_timestamp() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_activity("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	log_activity("has taken a fork", philo);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_activity("has taken a fork", philo);
	usleep_time(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}
