/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:23:58 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 16:27:56 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	create_processes(t_data *data)
{
	int			i;
	pthread_t	must_eat_thread;

	sem_wait(data->sem->pid_lock);
	if (data->must_eat_count != -1)
	{
		pthread_create(&must_eat_thread, NULL, eaten_enough, data);
		pthread_detach(must_eat_thread);
	}
	i = -1;
	while (++i < data->no_of_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
		{
			print_error("Fork failed");
			cleanup(data);
			exit(EXIT_FAILURE);
		}
		if (data->philo[i].pid == 0)
			philo_routine(&data->philo[i]);
	}
	sem_post(data->sem->pid_lock);
	waitpid(-1, NULL, 0);
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
