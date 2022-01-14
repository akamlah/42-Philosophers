/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:36:03 by alicekamlah       #+#    #+#             */
/*   Updated: 2022/01/14 13:58:40 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

/*
	Create semaphores for the syncronisation of the processes in the simulation.
*/
static int	phb_open_main_semaphores(t_ph_vars *phbx)
{
	sem_unlink(PHB_SEM_FORKS);
	phbx->sem_forks = sem_open(PHB_SEM_FORKS, O_CREAT | O_EXCL,
			S_IRWXU, phbx->number_of_philosophers);
	sem_unlink(PHB_SEM_PRINT);
	phbx->sem_print = sem_open(PHB_SEM_PRINT, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (phbx->sem_forks == SEM_FAILED || phbx->sem_print == SEM_FAILED)
		return (-1);
	return (0);
}

/*
	Initializes variables in main struct.
	Returns -1 on error.
	The check interval fo rthe timer is calibrated according to the number 
	of philosophers. Semaphores are opened.
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
	if (phb_open_main_semaphores(phbx) != 0)
	{
		perror("Init semaphores");
		return (-1);
	}	
	return (0);
}
