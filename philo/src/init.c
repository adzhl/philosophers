/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:09:44 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/24 21:02:30 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_data(t_data *data, int argc, char **argv)
{
    data->no_of_philo = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (argc == 6)
        data->must_eat_count = ft_atol(argv[5]);

}