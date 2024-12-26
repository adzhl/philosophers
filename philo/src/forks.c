/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:59:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/26 12:52:39 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->data->no_of_philo == 1)
	{
		usleep_time(philo->data->time_to_die);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		log_activity("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		log_activity("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		log_activity("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		log_activity("has taken a fork", philo);
	}
}

void	put_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

