/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:27:39 by abinti-a          #+#    #+#             */
/*   Updated: 2025/01/03 18:04:12 by abinti-a         ###   ########.fr       */
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

void	fork_error()
{
	print_error("Fork failed");
	exit(EXIT_FAILURE);
}

void	handle_single_philo(t_philo *philo)
{
	sem_wait(philo->sem->forks);
	log_activity("has taken a fork", philo);
	usleep_time(philo->data->time_to_die);
	sem_post(philo->sem->forks);
	log_activity("died", philo);
	exit(0);
}

void	cleanup(t_data *data)
{
	if (data->sem->forks)
		sem_close(data->sem->forks);
	if (data->sem->print_lock)
		sem_close(data->sem->print_lock);
	if (data->sem->stop_simulation)
		sem_close(data->sem->stop_simulation);
	if (data->sem->eating_lock)
		sem_close(data->sem->eating_lock);
	if (data->sem->meal_count_lock)
		sem_close(data->sem->meal_count_lock);
	if (data->sem->pid_lock)
		sem_close(data->sem->pid_lock);
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	sem_unlink("/stop_simulation");
	sem_unlink("/eating_lock");
	sem_unlink("/meal_count_lock");
	sem_unlink("/pid_lock");
	if (data->sem)
		free(data->sem);
	if (data->philo)
		free(data->philo);
}
