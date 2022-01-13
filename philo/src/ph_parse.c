/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:28 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/12 23:21:54 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

/* 
	prints usage instructions to stdout
 */
static void	ph_print_usage_msg(void)
{
	printf("Please enter:\n\
	<number_of_philosophers>\t\t\talso number of forks, positive integral\n\
	<time_to_die>\t\t\t\t\tin milliseconds (dev for min 60 ms)\n\
	<time_to_eat>\t\t\t\t\tin milliseconds (dev for min 60 ms)\n\
	<time_to_sleep>\t\t\t\t\tin milliseconds (dev for min 60 ms)\n\
	[<number_of_times_each_philosopher_must_eat>]\toptional\n");
}

/* 
	checks wether the argument is within the range of values allowed for an 
	integer if so returns 1, else 0.
 */
static int	ph_no_overflow(char *arg)
{
	long long	tmp;

	if (ft_strlen(arg) > 11)
		return (0);
	tmp = ft_atoi(arg);
	if (tmp <= INT_MIN || tmp >= INT_MAX)
		return (0);
	return (1);
}

/* 
	checks wether the given string is numerical
	skips initial whitespaces
 */
static int	ph_is_numerical_arg(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

/* 
	checks wether every argument is numerical and within the value range for
	integers.
	if so returns 1, else 0 after printing usage message to stdout.
 */
static int	ph_only_positive_integers_as_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ph_is_numerical_arg(argv[i]))
		{
			printf("Error: argument \"%s\": not a number\n", argv[i]);
			ph_print_usage_msg();
			return (0);
		}
		if (!ph_no_overflow(argv[i]))
		{
			printf("Error: argument \"%s\": out of boundaries. Enter a \
			positive integer.\n", argv[i]);
			return (0);
		}
		if (ft_atoi(argv[i]) < 0)
		{
			printf("Error: argument \"%s\": Cannot be negative.\n", argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
	If the number of arguments passed is not correct this function prints 
	usage message and returns error (-1).
	converts the arguments to integers and stores them in the datastructure.
	Returns -1 on error, 0 if none.
	Error messages are (unelegantly) printed by checkers.
*/
int	ph_parse(t_ph_vars *phx, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		if (argc < 5)
			printf("Error: too few arguments.\n");
		if (argc > 6)
			printf("Error: too many arguments.\n");
		ph_print_usage_msg();
		return (-1);
	}
	if (!ph_only_positive_integers_as_args(argv))
		return (-1);
	phx->number_of_philosophers = ft_atoi(argv[1]);
	if (phx->number_of_philosophers == 0)
	{
		printf("Error: 'numer_of_philosophers' has to be at least 1.\n");
		return (-1);
	}
	phx->time_to_die = ft_atoi(argv[2]);
	phx->time_to_eat = ft_atoi(argv[3]);
	phx->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		phx->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		phx->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}
