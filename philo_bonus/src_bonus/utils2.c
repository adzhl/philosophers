/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:34:05 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/28 23:27:38 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	is_digit(char *str)
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

void	print_error(char *message)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(STDERR_FILENO, message, i);
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
