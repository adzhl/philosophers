/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:23:58 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/30 18:33:13 by abinti-a         ###   ########.fr       */
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
	data->start_time = get_timestamp();
	i = -1;
	while (++i < data->no_of_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			fork_error(data);
		if (data->philo[i].pid == 0)
		{
			data->philo[i].creation_time = data->start_time;
			philo_routine(&data->philo[i]);
		}
	}
	sem_post(data->sem->pid_lock);
	waitpid(-1, NULL, 0);
}
