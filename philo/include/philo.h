/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:58:50 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/24 15:53:02 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// For printf (logging philosopher actions)
# include <stdio.h>

// For malloc and free
# include <stdlib.h>

// For usleep (sleeping) and write
# include <unistd.h>

// For memset (initializing memory)
# include <string.h>

// For gettimeofday (timestamp in milliseconds)
# include <sys/time.h>

// For pthread_create, pthread_join, mutexes, etc.
# include <pthread.h>

// For INT_MAX and INT_MIN
# include <limits.h>

# define ARG_NUM \
	"Error: Invalid number of arguments\n\
Follow this format: ./philo no_of_philo time_to_die time_to_eat time_to_sleep \
[no_of_times_each_philo_must_eat]\n"
# define ARG_1 "Error: no_of_philo must be a positive integer\n"
# define ARG_2 "Error: time_to_die must be a positive integer\n"
# define ARG_3 "Error: time_to_eat must be a positive integer\n"
# define ARG_4 "Error: time_to_sleep must be a positive integer\n"
# define ARG_5 "Error: no_of_times_each_philo_must_eat must be a positive integer\n"
# define PHILO_NUM "Error: There must be at least one philosopher\n"

// check args

int		check_args(int argc, char **argv);
int		valid_arg_count(int argc);
int		arg_is_valid(char **argv);
int		valid_arg_value(int num, int i);
void	arg_error(int i);

// utils

int		ft_isdigit(char *str);
long	ft_atol(char *str);

void	print_error(char *message);

#endif