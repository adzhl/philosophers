/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:03:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/29 16:04:01 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Simulation will stop when there is a philo death or
 * all philo had eaten enough
 */
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!end_simulation(data))
	{
		i = -1;
		while (++i < data->no_of_philo)
		{
			if (philo_death(data, i))
			{
				stop_simulation(data);
				return (NULL);
			}
		}
		if (eaten_enough(data))
		{
			stop_simulation(data);
			return (NULL);
		}
	}
	return (NULL);
}

/**
 * @brief eat_mutex is a shared resource (with philo_routine for eating).
 * Therefore, this resource needs to be locked with a mutex first before
 * accessing it.
 */
int	philo_death(t_data *data, int i)
{
	long	current_time;
	long	time_since_eaten;

	pthread_mutex_lock(&data->philo[i].eat_mutex);
	current_time = get_timestamp();
	time_since_eaten = current_time - data->philo[i].last_meal_time;
	if (time_since_eaten >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->philo[i].eat_mutex);
		log_activity("died", &data->philo[i]);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].eat_mutex);
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
		pthread_mutex_lock(&data->philo[i].meal_count_mutex);
		if (data->philo[i].meals_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->philo[i].meal_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].meal_count_mutex);
	}
	return (1);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->stop_lock);
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
