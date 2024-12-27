/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:09:44 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/27 23:26:32 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @return 0 (valid args)
 * @return 1 (invalid args)
 */
int	init_data(t_data *data, int argc, char **argv)
{
	data->no_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atol(argv[5]);
	else
		data->must_eat_count = -1;
	data->start_time = get_timestamp();
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->no_of_philo);
	sem_unlink("/print_lock");
	data->forks = sem_open("/print_lock", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/stop_simulation");
	data->forks = sem_open("/stop_simulation", O_CREAT | O_EXCL, 0644, 1);
	return (0);
}

/**
 * @brief initialize forks according to no_of_philo
 */
int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->no_of_philo);
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->no_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	return (1);
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	*assign_philo;

	data->philo = malloc(sizeof(t_philo) * data->no_of_philo);
	if (!data->philo)
		return (0);
	i = -1;
	while (++i < data->no_of_philo)
	{
		assign_philo = &data->philo[i];
		assign_philo->id = i + 1;
		assign_philo->last_meal_time = get_timestamp();
		assign_philo->meals_eaten = 0;
		assign_philo->left_fork = &data->forks[i];
		assign_philo->right_fork = &data->forks[(i + 1) % data->no_of_philo];
		assign_philo->data = data;
		pthread_mutex_init(&assign_philo->eat_mutex, NULL);
		pthread_mutex_init(&assign_philo->meal_count_mutex, NULL);
	}
	return (1);
}
