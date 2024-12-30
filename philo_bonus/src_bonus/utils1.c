/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:27:39 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 18:32:33 by abinti-a         ###   ########.fr       */
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
	timestamp = get_timestamp() - philo->creation_time;
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

void	fork_error(t_data *data)
{
	print_error("Fork failed");
	cleanup(data);
	exit(EXIT_FAILURE);
}

void	cleanup(t_data *data)
{
	sem_close(data->sem->forks);
	sem_close(data->sem->print_lock);
	sem_close(data->sem->stop_simulation);
	sem_close(data->sem->meal_lock);
	sem_close(data->sem->meal_count_lock);
	sem_close(data->sem->pid_lock);
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	sem_unlink("/stop_simulation");
	sem_unlink("/meal_lock");
	sem_unlink("/meal_count_lock");
	sem_unlink("/pid_lock");
	free(data->sem);
	free(data->philo);
}
