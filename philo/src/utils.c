/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:34:05 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/26 13:28:23 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/**
 * @note tv_sec contains whole seconds while
 * tv_usec tell the fraction of the second
 */
long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
	printf("%ld %d %s\n\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_lock);
}

/**
 * @brief usleep(500) is used to reduce CPU usage.
 * The function will check every 0.5 milliseconds to see
 * if the required duration is reached.
 */
void	usleep_time(int sleep_duration)
{
	long	start;

	start = get_timestamp();
	while (get_timestamp() - start < sleep_duration)
		usleep(500);
}

int	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	if (data->stop_simulation)
	{
		pthread_mutex_unlock(&data->stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_lock);
	return (0);
}
