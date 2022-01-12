#include "../header/philosophers.h"

static void ph_eat(t_ph_vars *phx, t_ph_philo *philo)
{
	ph_print_log(phx, philo, 1);
	philo->tsmp_lastmeal_msec = philo->tsmp_msec;
	ph_prec_msleep(phx->time_to_eat, phx->prec_sleep_interval);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->times_eaten += 1;
	if (philo->times_eaten == phx->number_of_times_each_philosopher_must_eat)
	{
		philo->ate_enough = 1;
		return ;
	}
	ph_print_log(phx, philo, 2);
	ph_prec_msleep(phx->time_to_sleep, phx->prec_sleep_interval);
}

static void ph_cyclus(t_ph_vars *phx, t_ph_philo *philo)
{

	if (philo->times_eaten)
		ph_print_log(phx, philo, 3);
	pthread_mutex_lock(philo->left_fork);
	ph_print_log(phx, philo, 0);
	pthread_mutex_lock(philo->right_fork);
	ph_print_log(phx, philo, 0);
	ph_eat(phx, philo);
}

static void *ph_philos_life(void *arg)
{
	t_ph_philo *philo;
	t_ph_vars *phx;

	philo = arg;
	phx = philo->ph_vars;

	while (!(phx->all_philos_created))
		usleep (3);
	if (!(philo->id % 2))
		ph_prec_msleep(phx->time_to_eat - (1), phx->prec_sleep_interval);
	while (1)
	{
		if (phx->someone_died)
			break ;
		ph_cyclus(phx, philo);
		if (philo->exitcode || philo->ate_enough)
			break ;
	}
	return NULL;
}

static t_ph_philo	*ph_new_philo(t_ph_vars *phx, int id)
{
	t_ph_philo *philo;

	philo = malloc(sizeof(t_ph_philo));
	if (!philo)
		return (NULL);
	philo->ph_vars = phx;
	philo->id = id;
	philo->ate_enough = 0;
	philo->tsmp_lastmeal_msec = phx->time_start_msec;
	philo->tsmp_msec = 0;
	philo->prev = phx->nth_philo;
	phx->nth_philo = philo;
	philo->exitcode = 0;
	philo->times_eaten = 0;
	if (philo->id < phx->number_of_philosophers)
		philo->right_fork = &phx->forks[philo->id];
	else
		philo->right_fork = &phx->forks[0];
	philo->left_fork = &phx->forks[philo->id - 1];
	return (philo);
}

int	ph_philo(t_ph_vars *phx, int id)
{
	t_ph_philo *philo;
	
	philo = ph_new_philo(phx, id);
	if (!philo)
		return (id);
	if (pthread_create(&philo->philo_thread, NULL, &ph_philos_life, (void*)philo) != 0)
	{
		perror("Error creating threads");
		return (id);
	}
	return (0);
}
