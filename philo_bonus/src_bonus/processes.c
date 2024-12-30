/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:23:58 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 09:28:05 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	create_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->no_of_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
		{
			print_error("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (data->philo[i].pid == 0)
		{
			philo_routine(&data->philo[i]);
			exit(EXIT_SUCCESS);
		}
	}
	monitor_routine(data);
}

void	cleanup(t_data *data)
{
	sem_close(data->sem->forks);
	sem_close(data->sem->print_lock);
	sem_close(data->sem->stop_simulation);
	sem_close(data->sem->meal_lock);
	sem_close(data->sem->meal_count_lock);
	free(data->philo);
}
