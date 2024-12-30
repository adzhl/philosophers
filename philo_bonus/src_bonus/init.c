/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:09:44 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 14:56:08 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

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
	//data->start_time = get_timestamp();
	data->sem = malloc(sizeof(t_sem));
	if (!data->sem)
		return (1);
	if (!init_philo(data) || !init_semaphore(data, data->no_of_philo))
		return (1);
	return (0);
}

/**
 * 1. Naming convention of semaphores starts with '/'
 * 2. sem_unlink() is called before initializing to remove semaphore with
 *    the same name from the system
 * 3. Semaphores are created as objects in the kernel that appear in the
 *    filesystem and exist in the system's shared memory space
 * 4. Permissions determine which processes can access the semaphore
 */
int	init_semaphore(t_data *data, int philo_count)
{
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	sem_unlink("/stop_simulation");
	sem_unlink("/meal_lock");
	sem_unlink("/meal_count_lock");
	data->sem->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, philo_count);
	data->sem->print_lock = sem_open("/print_lock", O_CREAT | O_EXCL, 0644, 1);
	data->sem->stop_simulation = sem_open("/stop_simulation", O_CREAT | O_EXCL, 0644,
			1);
	data->sem->meal_lock = sem_open("/meal_lock", O_CREAT | O_EXCL, 0644, 1);
	data->sem->meal_count_lock = sem_open("/meal_count_lock", O_CREAT | O_EXCL, 0644,
			1);
	if (data->sem->forks == SEM_FAILED || data->sem->print_lock == SEM_FAILED
		|| data->sem->stop_simulation == SEM_FAILED || data->sem->meal_lock == SEM_FAILED
		|| data->sem->meal_count_lock == SEM_FAILED)
		return (0);
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
		//assign_philo->last_meal_time = get_timestamp();
		assign_philo->meals_eaten = 0;
		assign_philo->pid = 0;
		assign_philo->sem = data->sem;
		assign_philo->data = data;
	}
	return (1);
}
