/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:59:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/25 18:00:35 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		log_activity("has taken a fork", philo->data);
		pthread_mutex_lock(philo->right_fork);
		log_activity("has taken a fork", philo->data);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		log_activity("has taken a fork", philo->data);
		pthread_mutex_lock(philo->left_fork);
		log_activity("has taken a fork", philo->data);
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
