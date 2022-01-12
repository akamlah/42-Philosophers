#include "../header/philosophers.h"

/*
	Creates an array of integers representing the forks and sets their status
	to 0 (0 = lies on table, 1 = is taken).
	Creates also an array of mutexes, one for every fork, and calls
	ptheread_mutex_init rouine for every one.
*/
int	ph_set_forks(t_ph_vars *phx)
{
	int i;

	phx->forks_status = malloc(sizeof(int) * phx->number_of_philosophers);
	if (!phx->forks_status)
		return (-1);
	phx->forks = malloc(sizeof(pthread_mutex_t) * phx->number_of_philosophers);
	if (!phx->forks)
		return (-1);
	i = 0;
	while (i < phx->number_of_philosophers)
	{
		if (pthread_mutex_init(&phx->forks[i], NULL) != 0)
			return (i);
		phx->forks_status[i] = 1;
		i++;
	}
	return (0);
}

void	ph_print_log(t_ph_vars *phx, t_ph_philo *philo, int msgnr);


void	*ph_death(void *arg)
{
	t_ph_philo	*philo;
	t_ph_vars	*phx;
	struct timeval tvx;

	phx = arg;
	while (1)
	{
		philo = phx->nth_philo;
		while (philo)
		{
			gettimeofday(&tvx, NULL);
			philo->tsmp_msec = 	(tvx.tv_usec / 1000) + (tvx.tv_sec * 1000) - phx->time_start_msec;
			// check philos need for food, kill it if starving
			if (philo->tsmp_msec - philo->tsmp_lastmeal_msec >= phx->time_to_die)
			{
				//philo->exitcode = 1; also useless var
				pthread_mutex_lock(&phx->someone_died_mutex);
				phx->someone_died = 1;
				pthread_mutex_unlock(&phx->someone_died_mutex);
				philo->exitcode = 1;
				ph_print_log(phx, philo, 4);
			//	no need if version 2
/* 				pthread_mutex_unlock(philo->left_fork);
				philo->has_lfork = 0;
				pthread_mutex_unlock(philo->right_fork);
				philo->has_rfork = 0; */
				return (NULL);
			}
			philo = philo->prev;
		}
		usleep(1000);
	}
}

int	ph_philo(t_ph_vars *phx, int id)
{
	t_ph_philo *philo;
	
	philo = ph_new_philo(phx, id);
	if (!philo)
		return (id);
	if (pthread_create(&philo->philo_thread, NULL, &ph_life, (void*)philo) != 0)
	{
		perror("Error creating threads");
		return (-1);
	}
		phx->all_init = 1;
	return (0);
}

/*
	joins the threads created for philos
*/
static int ph_join_philos(t_ph_vars *phx)
{
	t_ph_philo	*philo;
	
	philo = phx->nth_philo;
	while (philo != NULL)
	{
		if (pthread_join(philo->philo_thread, NULL) != 0)
		{
			perror("Error joining threads");
			return (-1);
		}
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
int ph_simulation(t_ph_vars *phx)
{
	int i;

	i = 0;
	// printf("notepme %d\n", phx->number_of_times_each_philosopher_must_eat);
	//phx->time_start_msec = ph_current_time_msec();
	while (i < phx->number_of_philosophers)
	{
		if (ph_philo(phx, i + 1) != 0)
			return (-1);
		i++;
	}

	if (pthread_create(&phx->death, NULL, &ph_death, phx))
	{
		perror("Error creating threads");
		return (-1);
	}
	// does joining order matter?? should i detatch death?
	if (pthread_join(phx->death, NULL))
	{
		perror("Error joining threads");
		return (-1);
	}
	ph_join_philos(phx);
	return (0);
}
