#include "../header/philosophers.h"




static void	ph_give_philo_his_forks(t_ph_philo *philo, t_ph_vars *phx)
{
	if (philo->id < phx->number_of_philosophers)
	{
		philo->right_fork = &phx->forks[philo->id];
		philo->right_fork_free = &phx->forks_status[philo->id];
	}
	else
	{
		philo->right_fork = &phx->forks[0];
		philo->right_fork_free = &phx->forks_status[0];
	}
	philo->left_fork = &phx->forks[philo->id - 1];
	philo->left_fork_free = &phx->forks_status[philo->id - 1];
}

/* 
static void	ph_give_philo_his_forks(t_ph_philo *philo, t_ph_vars *phx)
{
	if (philo->id < phx->number_of_philosophers)
		philo->right_fork = &phx->forks[philo->id];
	else
		philo->right_fork = &phx->forks[0];
	philo->left_fork = &phx->forks[philo->id - 1];
} */

t_ph_philo *ph_new_philo(t_ph_vars *phx, int id)
{
	t_ph_philo *philo;

	philo = malloc(sizeof(t_ph_philo));
	if (!philo)
		return (NULL);
	philo->ph_vars = phx;
	philo->id = id;
	philo->status = 0;
	philo->tsmp_lastmeal_msec = phx->time_start_msec;
	philo->tsmp_msec = 0;
	philo->has_lfork = 0;
	philo->has_rfork = 0;

	philo->prev = phx->nth_philo;
	phx->nth_philo = philo;

	philo->exitcode = 0;
	pthread_mutex_init(&philo->exit_mtx, NULL);
	philo->times_eaten = 0;
	
	ph_give_philo_his_forks(philo, phx);

	return (philo);
}

