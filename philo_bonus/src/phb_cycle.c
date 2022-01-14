/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:38:28 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/14 14:06:31 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

/*
	The usleep() function suspends execution of the calling thread
	for (at least) usec microseconds. The sleep may be lengthened
	slightly by any system activity or by the time spent processing
	the call or by the granularity of system timers.
	need a clock thread if i want to do error handeling, or all ifs 
	kill performance.
*/
int	ph_prec_msleep(long tv_tosleep_msec, int interval)
{
	struct timeval	tvx;
	long			start;
	long			now;
	long			tosleep;

	gettimeofday(&tvx, NULL);
	start = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	now = start;
	tosleep = start + tv_tosleep_msec;
	while (now < tosleep)
	{
		usleep(interval);
		gettimeofday(&tvx, NULL);
		now = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	}
	return (0);
}

/*
	Finctionality for printing the log messages to stdout with a good enough
	timestamp. If someone died or the philo has eaten enough it stops printing.
*/
static void	phb_print_log(t_ph_vars *phbx, t_ph_philo *philo, int msgnr)
{
	char			*msg[5];
	struct timeval	tvx;

	msg[0] = "has taken a fork";
	msg[1] = "is eating";
	msg[2] = "is sleeping";
	msg[3] = "is thinking";
	msg[4] = "died";
	sem_wait(philo->sem_print);
	gettimeofday(&tvx, NULL);
	philo->tsmp_msec = ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000))
		- phbx->time_start_msec;
	if (msgnr != 4 && !philo->ate_enough)
	{
		printf("%ld %d %s\n", philo->tsmp_msec, philo->id, msg[msgnr]);
		sem_post(philo->sem_print);
	}
	if (msgnr == 4 && !philo->ate_enough)
		printf("%ld %d %s\n", ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000))
			- phbx->time_start_msec, philo->id, msg[msgnr]);
}

/*
	Death control thread for the single philosopher. 
	Monitors his process in intervals of 1ms.
	Sends SIGINT to the process if conditions for death are met.
*/
void	*phb_death(void *arg)
{
	t_ph_philo		*philo;
	t_ph_vars		*phbx;
	struct timeval	tvx;

	philo = arg;
	phbx = philo->ph_vars;
	while (1)
	{
		gettimeofday(&tvx, NULL);
		philo->tsmp_msec = (tvx.tv_usec / 1000)
			+ (tvx.tv_sec * 1000) - phbx->time_start_msec;
		if (philo->tsmp_msec - philo->tsmp_lastmeal_msec
			>= phbx->time_to_die)
		{
			phb_print_log(phbx, philo, 4);
			kill(philo->pid, SIGINT);
			exit(0);
		}
		usleep(1000);
	}
}

/*
	Cyclic function that each process executes unless killed by death or, if the
	optional argument is specified, they ate enough times.
*/
void	phb_philos_life(t_ph_vars *phbx, t_ph_philo *philo)
{
	if (philo->id % 2 == 0)
		ph_prec_msleep(phbx->time_to_eat - 1, phbx->prec_sleep_interval);
	while (1)
	{
		if (philo->times_eaten)
			phb_print_log(phbx, philo, 3);
		sem_wait(philo->sem_forks);
		phb_print_log(phbx, philo, 0);
		sem_wait(philo->sem_forks);
		phb_print_log(phbx, philo, 0);
		phb_print_log(phbx, philo, 1);
		philo->tsmp_lastmeal_msec = philo->tsmp_msec;
		ph_prec_msleep(phbx->time_to_eat, phbx->prec_sleep_interval);
		sem_post(philo->sem_forks);
		sem_post(philo->sem_forks);
		philo->times_eaten += 1;
		if (philo->times_eaten
			== phbx->number_of_times_each_philosopher_must_eat)
			return ;
		phb_print_log(phbx, philo, 2);
		ph_prec_msleep(phbx->time_to_sleep, phbx->prec_sleep_interval);
	}
}
