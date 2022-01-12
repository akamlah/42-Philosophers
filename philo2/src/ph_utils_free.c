#include "../header/philosophers.h"





/* 
	frees up to n forks. If a -1 is passed, it means all possible 
	forks were allocated and thus n is set to max possible, i.e.
	number_of_philosophers.
 */
static void	ph_free_forks(t_ph_vars *phx, int n)
{
	int i;

	i = 0;
	if (n == -1)
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
	Frees up to n philosophers. If n = -1, it is assumed all possible
	Philosophers were created, thus n is set to number_of_philosophers.
 */
static void	ph_free_philos(t_ph_vars *phx, int n)
{
	t_ph_philo	*curr;
	t_ph_philo	*tmp;
	int			i;

	i = 0;
	if (n == -1)
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
void ph_free(t_ph_vars *phx, int forks, int philos)
{
	if (forks)
		ph_free_forks(phx, forks);
	if (philos)
		ph_free_philos(phx, philos);
	pthread_mutex_destroy(&phx->someone_died_mutex);
	pthread_mutex_destroy(&phx->print_mutex);
}

