/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:56:06 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/25 13:57:00 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @return 0 (valid args)
 * @return 1 (invalid args)
 */
int	check_args(int argc, char **argv)
{
	if (!valid_arg_count(argc))
		return (1);
	if (!arg_is_valid(argv))
		return (1);
	return (0);
}

int	valid_arg_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		print_error(ARG_NUM);
		return (0);
	}
	return (1);
}

int	arg_is_valid(char **argv)
{
	int		i;
	long	num;

	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
		{
			arg_error(i);
			return (0);
		}
		num = ft_atol(argv[i]);
		if (num < INT_MIN || num > INT_MAX)
		{
			arg_error(i);
			return (0);
		}
		if (!valid_arg_value(num, i))
			return (0);
		i++;
	}
	return (1);
}

int	valid_arg_value(int num, int i)
{
	if (i == 1 && num < 1)
	{
		print_error(PHILO_NUM);
		return (0);
	}
	else if (i != 1 && num <= 0)
	{
		arg_error(i);
		return (0);
	}
	return (1);
}

void	arg_error(int i)
{
	if (i == 1)
		print_error(ARG_1);
	else if (i == 2)
		print_error(ARG_2);
	else if (i == 3)
		print_error(ARG_3);
	else if (i == 4)
		print_error(ARG_4);
	else if (i == 5)
		print_error(ARG_5);
}
