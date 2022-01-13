/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:21 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 19:44:39 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

/* ************************************************************************** */
//	MAIN
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_ph_vars	phbx;

	if (ph_parse(&phbx, argc, argv) != 0)
		return (1);
	if (phb_init(&phbx) != 0)
		return (2);
	phb_simulation(&phbx);
	
	sem_close(phbx.sem_forks);
	sem_close(phbx.sem_print);
	return (0);
}

/* ************************************************************************** */
//	Free heap at program end
/* ************************************************************************** */

/*
	Frees up to n philosophers. If n = -2, it is assumed all possible
	Philosophers were created, thus n is set to number_of_philosophers.
*/
static void	ph_free_philos(t_ph_vars *phbx, int n)
{
	t_ph_philo	*curr;
	t_ph_philo	*tmp;
	int			i;

	i = 0;
	if (n == -2)
		n = phbx->number_of_philosophers;
	curr = phbx->nth_philo;
	while (i < n)
	{
		tmp = curr;
		curr = curr->prev;
		free(tmp);
		i++;
	}
}

/*
	Checks if one of the above can be called and destroys all mutexes
*/
/* void	ph_free(t_ph_vars *phbx, int forks, int philos)
{
	if (forks)
		ph_free_forks(phbx, forks);
	if (philos)
		ph_free_philos(phbx, philos);
	pthread_mutex_destroy(&phbx->someone_died_mutex);
	pthread_mutex_destroy(&phbx->print_mutex);
}
 */