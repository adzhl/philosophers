/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:34:05 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/24 15:53:39 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
    if (!str || !*str)
        return (0);
    while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
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
	int	sign;
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
