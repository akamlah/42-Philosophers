/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:39 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 00:44:40 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

/*
	Initializes variables in main struct.
	Returns -1 on error.
	The check interval fo rthe timer is calibrated according to the number 
	of philosophers.
*/
int	ph_init(t_ph_vars *phx)
{
	struct timeval	tvx;

	if (gettimeofday(&tvx, NULL))
	{
		perror("Error getting satrt time");
		return (-1);
	}
	phx->time_start_msec = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	phx->nth_philo = NULL;
	if (pthread_mutex_init(&phx->print_mutex, NULL))
	{
		perror("Error initializing mutexes");
		return (-1);
	}
	phx->someone_died = 0;
	phx->all_philos_created = 0;
	if (phx->number_of_philosophers < 150)
		phx->prec_sleep_interval = 100;
	else
		phx->prec_sleep_interval = 500;
	return (0);
}

/*
	Creates an array of integers representing the forks and sets their status
	to 0 (0 = lies on table, 1 = is taken).
	Creates also an array of mutexes, one for every fork, and calls
	ptheread_mutex_init rouine for every one.
*/
int	ph_init_forks(t_ph_vars *phx)
{
	int	i;

	phx->forks = malloc(sizeof(pthread_mutex_t) * phx->number_of_philosophers);
	if (!phx->forks)
		return (-1);
	i = 0;
	while (i < phx->number_of_philosophers)
	{
		if (pthread_mutex_init(&phx->forks[i], NULL) != 0)
		{
			perror("Error initializing mutexes");
			return (i);
		}
		i++;
	}
	return (0);
}

/*
	Thread on itself that every 1 ms checks if a philosopher has starved to
	death. If so, it kills it by setting an exit flag to true (1) and also a
	globally readable flag that someone died to true so that the other threads
	stop printing logs and return to the main (kill function in "log_and_time")
	The sum of all 'ate enough' flags is as a precaution so that this thread
	can return even if the program ends by the 5th argument's effect and not
	instead of a philosopher's death.
*/
static void	*ph_death(void *arg)
{
	t_ph_philo		*philo;
	t_ph_vars		*phx;
	struct timeval	tvx;
	int				sum;

	phx = arg;
	while (1)
	{
		sum = 0;
		philo = phx->nth_philo;
		while (philo)
		{
			gettimeofday(&tvx, NULL);
			philo->tsmp_msec = (tvx.tv_usec / 1000)
				+ (tvx.tv_sec * 1000) - phx->time_start_msec;
			if (philo->tsmp_msec - philo->tsmp_lastmeal_msec
				>= phx->time_to_die)
				return (ph_kill_philo(phx, philo));
			sum += philo->ate_enough;
			if (sum == phx->number_of_philosophers)
				return (NULL);
			philo = philo->prev;
		}
		usleep(1000);
	}
}

/*
	joins the threads created for philos, so that the main doea not end before
	they have returned to it.
*/
static int	ph_join_philos(t_ph_vars *phx)
{
	t_ph_philo	*philo;

	philo = phx->nth_philo;
	while (philo != NULL)
	{
		if (pthread_join(philo->philo_thread, NULL) != 0)
			return (-1);
		philo = philo->prev;
	}
	return (0);
}

/*
	Launches the building function, wich generates threads, catches its error
	and if none it runs pthread join on every thread in order for the main
	to wait for them finishing before quitting the program.
	(The errors are sent to main as -1 is returned)
*/
int	ph_simulation(t_ph_vars *phx)
{
	int	i;
	int	err;

	i = 0;
	while (i < phx->number_of_philosophers)
	{
		err = ph_philo(phx, i + 1);
		if (err)
			return (err);
		i++;
	}
	if (pthread_create(&phx->death, NULL, &ph_death, phx))
	{
		perror("Error creating threads");
		return (-1);
	}
	phx->all_philos_created = 1;
	if (pthread_join(phx->death, NULL) || ph_join_philos(phx))
	{
		perror("Error joining threads");
		return (-1);
	}
	return (0);
}
