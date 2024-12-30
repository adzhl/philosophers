/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:23:58 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 08:36:35 by abinti-a         ###   ########.fr       */
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
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_close(data->stop_simulation);
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	sem_unlink("/stop_simulation");
}
