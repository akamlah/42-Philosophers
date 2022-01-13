/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_log_and_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:13 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 00:27:43 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

/*
	Finctionality for printing the log messages to stdout with a good enough
	timestamp. If someone died or the philo has eaten enough it stops printing.
*/
void	ph_print_log(t_ph_vars *phx, t_ph_philo *philo, int msgnr)
{
	char			*msg[5];
	struct timeval	tvx;

	msg[0] = "has taken a fork";
	msg[1] = "is eating";
	msg[2] = "is sleeping";
	msg[3] = "is thinking";
	msg[4] = "died";
	pthread_mutex_lock(&phx->print_mutex);
	gettimeofday(&tvx, NULL);
	philo->tsmp_msec = ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000))
		- phx->time_start_msec;
	if (msgnr != 4 && !phx->someone_died && !philo->ate_enough)
		printf("%ld %d %s\n", philo->tsmp_msec, philo->id, msg[msgnr]);
	if (msgnr == 4 && !philo->ate_enough)
		printf("%ld %d %s\n", ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000))
			- phx->time_start_msec, philo->id, msg[msgnr]);
	pthread_mutex_unlock(&phx->print_mutex);
}

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
	Part of the death thread functionality that kills a thread by setting
	his exutflag to true and also the globally readable flag that someone died
	so that the other philos stop printing and return.
*/
void	*ph_kill_philo(t_ph_vars *phx, t_ph_philo *philo)
{
	phx->someone_died = 1;
	philo->exitcode = 1;
	ph_print_log(phx, philo, 4);
	return (NULL);
}
