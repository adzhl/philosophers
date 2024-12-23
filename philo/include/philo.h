/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:58:50 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/23 20:05:42 by abinti-a         ###   ########.fr       */
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

#endif