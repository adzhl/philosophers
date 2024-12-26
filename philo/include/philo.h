/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:58:50 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/26 09:33:08 by abinti-a         ###   ########.fr       */
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

# define MAX_PHILO 200
# define MIN_VALUE 60
# define ARG_NUM \
	"Error: Invalid number of arguments\n\
Follow this format: ./philo no_of_philo time_to_die time_to_eat time_to_sleep \
[no_of_times_each_philo_must_eat]\n"
# define ARG_1 "Error: no_of_philo must be a positive integer\n"
# define ARG_2 "Error: time_to_die must be a positive integer\n"
# define ARG_3 "Error: time_to_eat must be a positive integer\n"
# define ARG_4 "Error: time_to_sleep must be a positive integer\n"
# define ARG_5 \
	"Error: no_of_times_each_philo_must_eat must be a positive \
integer\n"
# define PHILO_NUM "Error: There must be at least one philosopher\n"
# define ERR_MAX_PHILO "Error: No of philosophers cannot exceed 200\n"
# define ERR_2 "Error: time_to_die cannot be lower than 60\n"
# define ERR_3 "Error: time_to_eat cannot be lower than 60\n"
# define ERR_4 "Error: time_to_sleep cannot be lower than 60\n"
# define ERR_5 "Error: no_of_times_each_philo_must_eat must be at least 1\n"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					no_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	long				start_time;
	int					stop_simulation;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		stop_lock;
	t_philo				*philo;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	long				last_meal_time;
	int					meals_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		meal_count_mutex;
}						t_philo;

// check args

int						check_args(int argc, char **argv);
int						valid_arg_count(int argc);
int						arg_is_valid(char **argv);
int						valid_arg_value(int num, int i);
void					arg_error(int i);

// initialize data

int						init_data(t_data *data, int argc, char **argv);
int						init_forks(t_data *data);
int						init_philo(t_data *data);

// thread creation

void					create_threads(t_data *data);

// routine

void					*philo_routine(void *arg);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);

// monitoring

void					*monitor_routine(void *arg);
int						philo_death(t_data *data, int i);
int						eaten_enough(t_data *data);
void					stop_simulation(t_data *data);
void					meal_count_reached(t_data *data);

// forks

void					take_fork(t_philo *philo);
void					put_fork(t_philo *philo);

// cleanup

void					cleanup(t_data *data);

// utils

int						ft_isdigit(char *str);
long					ft_atol(char *str);
long					get_timestamp(void);
void					log_activity(char *message, t_data *data);
void					usleep_time(int sleep_duration);

void					print_error(char *message);

#endif