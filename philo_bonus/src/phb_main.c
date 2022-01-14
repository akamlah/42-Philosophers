/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:21 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/14 12:37:07 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

/* ************************************************************************** */
//	MAIN
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_ph_vars	phbx;
	int			err;

	if (ph_parse(&phbx, argc, argv) != 0)
		return (1);
	if (phb_init(&phbx) != 0)
		return (1);
	err = phb_simulation(&phbx);
	if (err)
		phb_free_and_exit(&phbx, err, 2);
	phb_free_and_exit(&phbx, err, 0);
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
void	phb_free_and_exit(t_ph_vars *phbx, int philos, int exitstatus)
{
	if (philos)
		ph_free_philos(phbx, philos);
	sem_close(phbx->sem_forks);
	sem_close(phbx->sem_print);
	exit (exitstatus);
}
