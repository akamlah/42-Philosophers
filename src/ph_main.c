#include "../header/philosophers.h"

/* ************************************************************************** */
// MAIN
/* ************************************************************************** */

// todo: 
// do i have to check if time ags given are > 0? what happens if = 0?
// edge case 0 or 1 philo covered?
// destroyed and freed all mutexes?
// how avoid philos printng stuff at same timestamp? -> now i will try to cut to ms only at the moment of printnig to propagate less errors in the conversions

int main(int argc, char **argv)
{
	t_ph_vars	phx;
	int err;

	if (ph_parse(&phx, argc, argv) != 0)
		return (1);
	if (ph_init(&phx) != 0)
		return (2);
	err = ph_init_forks(&phx);
	if (err)
	{
		ph_free(&phx, err, 0);
		return (3);
	}
	err = ph_simulation(&phx);
	if (err)
	{
		ph_free(&phx, -2, err);
		return (4);
	}
	ph_free(&phx, -2, -2);
	return (0);
}


/* ************************************************************************** */

//	Free functionalities

/* ************************************************************************** */

/*
	frees up to n forks. If a -2 is passed, it means all possible 
	forks were allocated and thus n is set to max possible, i.e.
	number_of_philosophers.
 */
static void	ph_free_forks(t_ph_vars *phx, int n)
{
	int i;

	i = 0;
	if (n == -2)
		n = phx->number_of_philosophers;
	while (i < n)
	{
		pthread_mutex_destroy(&phx->forks[i]);
		i++;
	}
	if (phx->forks)
		free(phx->forks);
}

/* 
	Frees up to n philosophers. If n = -2, it is assumed all possible
	Philosophers were created, thus n is set to number_of_philosophers.
 */
static void	ph_free_philos(t_ph_vars *phx, int n)
{
	t_ph_philo	*curr;
	t_ph_philo	*tmp;
	int			i;

	i = 0;
	if (n == -2)
		n = phx->number_of_philosophers;
	curr = phx->nth_philo;
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
void	ph_free(t_ph_vars *phx, int forks, int philos)
{
	if (forks)
		ph_free_forks(phx, forks);
	if (philos)
		ph_free_philos(phx, philos);
	pthread_mutex_destroy(&phx->someone_died_mutex);
	pthread_mutex_destroy(&phx->print_mutex);
}
