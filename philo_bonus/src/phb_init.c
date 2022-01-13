/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:33 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 19:44:11 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

/*
	PHILOSOPHER
*/
int	phb_philo(t_ph_vars *phbx, int id)
{
	t_ph_philo	*philo;

	philo = phb_new_philo(phbx, id);
	if (!philo)
		return (id);
	philo->pid = fork();
	if (philo->pid < 0)
	{
		perror("Error forking");
		return (-1);
	}
	if (philo->pid == 0) // CHILD PROCESS
	{
		// open existing semaphores
		philo->sem_forks = sem_open(PHB_SEM_FORKS, 0);
		philo->sem_print = sem_open(PHB_SEM_PRINT, 0);
		if (philo->sem_forks == SEM_FAILED || philo->sem_print == SEM_FAILED)
		{
			perror("Error semaphore child process");
			exit(1);
		}

		struct timeval	tvx;
		gettimeofday(&tvx, NULL);
		philo->tsmp_msec = ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000))
			- phbx->time_start_msec;
		// create death thread
		if (pthread_create(&phbx->death, NULL, &phb_death, (void *)philo))
			return (-1);
		phb_philos_life(phbx, philo); // returns to this point if ended by something
		if (pthread_detach(phbx->death))
			return (-1);
/* 		if (pthread_join(phbx->death, NULL))
			return (-1); */
		// seems to make no difference 
		exit(0); // EXIT BEFORE GOING BACK IN WHILE LOOP and forking all the next philos!
	}
	return (0);
}


/*

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
//	pthread_cerate(&phbx->death, NULL, &phb_death, );
	philo = phbx->nth_philo;
	while (philo != NULL)
	{
		waitpid(philo->pid, NULL, 0);
		philo = philo->prev;
	}
	//waitpid(-1, NULL, 0);
	return (0);
}

/*
	Initializes variables in main struct.
	Returns -1 on error.
	The check interval fo rthe timer is calibrated according to the number 
	of philosophers.
*/
int	phb_init(t_ph_vars *phbx)
{
	struct timeval	tvx;

	if (gettimeofday(&tvx, NULL))
	{
		perror("Error getting satrt time");
		return (-1);
	}
	phbx->time_start_msec = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	phbx->nth_philo = NULL;

	if (phbx->number_of_philosophers < 150)
		phbx->prec_sleep_interval = 100;
	else
		phbx->prec_sleep_interval = 500;

	sem_unlink(PHB_SEM_FORKS);
	phbx->sem_forks = sem_open(PHB_SEM_FORKS, O_CREAT | O_EXCL, S_IRWXU, phbx->number_of_philosophers);
	sem_unlink(PHB_SEM_PRINT);
	phbx->sem_print = sem_open(PHB_SEM_PRINT, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (phbx->sem_forks == SEM_FAILED || phbx->sem_print == SEM_FAILED)
	{
		perror("Init semaphores");
		exit(1);
	}
	return (0);
}

/*
	Constructor for philosopher
	
	Allocates memory for a new philosopher and sets initial values,
	insert the node in the linked list and links the addresses of the forks
	and other data to the pointers allocated accordingly.
*/
t_ph_philo	*phb_new_philo(t_ph_vars *phbx, int id)
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

