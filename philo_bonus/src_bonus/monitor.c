/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:03:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/29 15:47:45 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

/**
 * @brief Simulation will stop when there is a philo death or
 * all philo had eaten enough
 */
void	monitor_routine(t_data *data)
{
	int		i;
	int		status;

	while (1)
	{
		i = -1;
		while (++i < data->no_of_philo)
		{
			if (philo_death(data, i))
			{
				sem_wait(data->stop_simulation);
				stop_simulation(data);
				return ;
			}
		}
		if (eaten_enough(data))
			break ;
	}
	i = -1;
	while (++i < data->no_of_philo)
		waitpid(data->philo[i].pid, &status, 0);
}

int	philo_death(t_data *data, int i)
{
	long	current_time;
	long	time_since_eaten;

	current_time = get_timestamp();
	time_since_eaten = current_time - data->philo[i].last_meal_time;
	if (time_since_eaten >= data->time_to_die)
	{
		log_activity("died", &data->philo[i]);
		return (1);
	}
	return (0);
}

/**
 * @brief iterate through every philosopher to check
 * if all of them had eaten enough
 */
int	eaten_enough(t_data *data)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = -1;
	while (++i < data->no_of_philo)
	{
		if (data->philo[i].meals_eaten < data->must_eat_count)
			return (0);
	}
	return (1);
}

void	stop_simulation(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->no_of_philo)
		kill(data->philo[i].pid, SIGKILL);
}
