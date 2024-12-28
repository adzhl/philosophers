/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:56:11 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/28 23:24:32 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	create_threads(&data);
	cleanup(&data);
	return (0);
}
