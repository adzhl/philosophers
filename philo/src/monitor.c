/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:03:17 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/26 12:58:36 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Simulation will stop when there is a philo death or
 * all philo had eaten enough
 */
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (1)
	{
        if (end_simulation(data))
            break;
		while (++i < data->no_of_philo)
		{
			if (philo_death(data, i))
			{
				stop_simulation(data);
                end_simulation(data);
				return (NULL);
			}
		}
        if (eaten_enough(data))
        {
            stop_simulation(data);
            end_simulation(data);
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
    printf("time_since_eaten %ld\n", time_since_eaten);
    printf("time_to_die %d\n", data->time_to_die);
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
	int	not_hungry;

    if (data->must_eat_count == -1)
        return (0);
    i = -1;
	not_hungry = 0;
	while (++i < data->no_of_philo)
	{
        pthread_mutex_lock(&data->philo[i].meal_count_mutex);
		if (data->philo[i].meals_eaten >= data->must_eat_count)
			not_hungry++;
        pthread_mutex_unlock(&data->philo[i].meal_count_mutex);
	}
	if (not_hungry == data->no_of_philo)
	{
		//meal_count_reached(data);
        end_simulation(data);
		return (1);
	}
	return (0);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->stop_lock);
}

void	meal_count_reached(t_data *data)
{
	pthread_mutex_lock(&data->print_lock);
	printf("All philosophers have eaten enough. Ending simulation.\n");
	pthread_mutex_unlock(&data->print_lock);
}
