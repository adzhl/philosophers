/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:27:39 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 09:36:48 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

/**
 * @brief Activity logging is a shared resource.
 * Therefore, it must be locked before using and unlocked after using
 */
void	log_activity(char *message, t_philo *philo)
{
	long	timestamp;

	sem_wait(philo->sem->print_lock);
	timestamp = get_timestamp() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, message);
	if (ft_strcmp(message, "died") != 0)
		sem_post(philo->sem->print_lock);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
