/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:56:11 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/26 09:18:12 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int check_initialization(t_data *data)
// {
// 	printf("no of philo: %d\n", data->no_of_philo);
// 	printf("time to die: %d\n", data->time_to_die);
// 	printf("time to eat: %d\n", data->time_to_eat);
// 	printf("time to sleep: %d\n", data->time_to_sleep);
// 	printf("must eat count: %d\n", data->must_eat_count);
// 	printf("time to eat: %d\n", data->time_to_eat);
// 	printf("stop simulation: %d\n", data->stop_simulation);
//     for (int i = 0; i < data->no_of_philo; i++)
//     {
//         t_philo *philo = &data->philo[i]; // Access each philosopher
//         printf("Philosopher %d:\n", philo->id);
//         printf("  Last meal time: %ld\n", philo->last_meal_time);
//         printf("  Meals eaten: %d\n", philo->meals_eaten);
//         printf("  Left fork address: %p\n", (void *)philo->left_fork);
//         printf("  Right fork address: %p\n", (void *)philo->right_fork);
//     }
//     return (0);
// }

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	create_threads(&data);
	return (0);
}
