/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:33 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/14 14:06:20 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

/*
	Control function for the lifecycle inside child process.
	
	Opens semaphores in child process, sets initial timestamp and creates a
	'death' control thread that kills the process if conditions for that are
	met. 
	Exits with 1 on failure, 0 on success.
*/
static int	phb_philo_process(t_ph_vars *phbx, t_ph_philo *philo)
{
	struct timeval	tvx;

	philo->sem_forks = sem_open(PHB_SEM_FORKS, 0);
	philo->sem_print = sem_open(PHB_SEM_PRINT, 0);
	if (philo->sem_forks == SEM_FAILED || philo->sem_print == SEM_FAILED)
	{
		perror("Error semaphore child process");
		exit(1);
	}
	gettimeofday(&tvx, NULL);
	philo->tsmp_msec
		= ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000)) - phbx->time_start_msec;
	if (pthread_create(&phbx->death, NULL, &phb_death, (void *)philo))
	{
		perror("Error control thread create");
		exit(1);
	}
	phb_philos_life(phbx, philo);
	if (pthread_detach(phbx->death))
	{
		perror("Error control thread join");
		exit(1);
	}
	exit(0);
}

/*
	Constructor for philosopher
	
	Allocates memory for a new philosopher and sets initial values
	and insert the node in the linked list.
	Returns null on failure, or the address of the new element on success.
*/
static t_ph_philo	*phb_new_philo(t_ph_vars *phbx, int id)
{
	t_ph_philo	*philo;

	philo = malloc(sizeof(t_ph_philo));
	if (!philo)
		return (NULL);
	philo->ph_vars = phbx;
	philo->id = id;
	philo->ate_enough = 0;
	philo->tsmp_lastmeal_msec = 0;
	philo->tsmp_msec = 0;
	philo->prev = phbx->nth_philo;
	phbx->nth_philo = philo;
	philo->times_eaten = 0;
	return (philo);
}

/*
	PHILOSOPHER

	A new philosopher is created, initialized, and a child process launched.
	Returns the philosophers id on error, else zero is returned.
*/
static int	phb_philo(t_ph_vars *phbx, int id)
{
	t_ph_philo	*philo;

	philo = phb_new_philo(phbx, id);
	if (!philo)
		return (id);
	philo->pid = fork();
	if (philo->pid < 0)
	{
		perror("Error forking");
		return (philo->id);
	}
	if (philo->pid == 0)
	{
		if (phb_philo_process(phbx, philo))
			return (philo->id);
	}
	return (0);
}

/*
	CONTROL FUNCTION for whole simulation

	The single philosophers are created and thy return to this function that waits
	for them to be finished before returning to the main.
	On allocation or forking or process failure of a philosopher it returns his id 
	non-zero positive value).
*/
int	phb_simulation(t_ph_vars *phbx)
{
	int				i;
	int				err;
	t_ph_philo		*philo;

	i = 0;
	while (i < phbx->number_of_philosophers)
	{
		err = phb_philo(phbx, i + 1);
		if (err)
			return (err);
		i++;
	}
	philo = phbx->nth_philo;
	while (philo != NULL)
	{
		waitpid(philo->pid, NULL, 0);
		philo = philo->prev;
	}
	return (0);
}
