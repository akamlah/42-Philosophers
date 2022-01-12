#include "../header/philosophers.h"
// The challenge in the dining philosophers problem is to design a protocol so 
// that the philosophers do not deadlock (i.e. every philosopher has a 
// chopstick), and so that no philosopher starves (i.e. when a philosopher is 
// hungry, he/she eventually gets the chopsticks).

void	ph_print_log(t_ph_vars *phx, t_ph_philo *philo, int msgnr)
{
	char *msg[5] = {"has taken a fork", "is eating", "is sleeping", "is thinking", "died"};


	struct timeval tvx;

	pthread_mutex_lock(&phx->print_mutex);
	gettimeofday(&tvx, NULL);
	philo->tsmp_msec = ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000)) - phx->time_start_msec;
	if (msgnr != 4 && !phx->someone_died)
		printf("%ld %d %s\n", philo->tsmp_msec, philo->id, msg[msgnr]);
	if (msgnr == 4)
		printf("%ld %d %s\n", ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000)) - phx->time_start_msec, philo->id, msg[msgnr]);
	pthread_mutex_unlock(&phx->print_mutex);
}

void ph_eat(t_ph_vars *phx, t_ph_philo *philo)
{
	ph_print_log(phx, philo, 1);
	philo->tsmp_lastmeal_msec = philo->tsmp_msec;
	ph_prec_msleep(phx->time_to_eat);
/* 	*(philo->right_fork_free) = 1; */
	pthread_mutex_unlock(philo->right_fork);
/* 		pthread_mutex_lock(&phx->print_mutex);
		printf("%ld %d lost right fork (%p)\n", philo->tsmp_msec, philo->id, philo->right_fork);
		pthread_mutex_unlock(&phx->print_mutex); */
/* 	*(philo->left_fork_free) = 1; */
	pthread_mutex_unlock(philo->left_fork);
/* 		pthread_mutex_lock(&phx->print_mutex);
		printf("%ld %d lost left fork (%p)\n", philo->tsmp_msec, philo->id, philo->left_fork);
		pthread_mutex_unlock(&phx->print_mutex); */
/* 	philo->status = 2; */
	philo->times_eaten += 1;

if (philo->times_eaten == phx->number_of_times_each_philosopher_must_eat)
		{
			philo->status = 3;
			return ;
		}
			ph_print_log(phx, philo, 2);
			int delay = philo->tsmp_msec - (philo->tsmp_lastmeal_msec + phx->time_to_eat);
			pthread_mutex_lock(&phx->print_mutex_islocked_lock);
			phx->time_start_msec += delay;
			pthread_mutex_unlock(&phx->print_mutex_islocked_lock);
			ph_prec_msleep(phx->time_to_sleep); // - delay * 2);


/* 			pthread_mutex_lock(&phx->print_mutex);
			printf("%ld %d awake\n", ph_current_time_msec() - phx->time_start_msec, philo->id);
			pthread_mutex_unlock(&phx->print_mutex); */
		//	philo->status = 3;


}

void ph_cyclus(t_ph_vars *phx, t_ph_philo *philo)
{

		if (philo->status == 1)
		{
			ph_print_log(phx, philo, 3); // is thinking
			philo->status = 2;
		}
		// if ! prio return

/* 				pthread_mutex_lock(&phx->print_mutex);
				printf("%ld %d waiting for forks \n", ph_current_time_msec() - phx->time_start_msec, philo->id);
				pthread_mutex_unlock(&phx->print_mutex); */
/* if (!(philo->id % 2))
{
	pthread_mutex_lock(philo->right_fork);
ph_prec_msleep(100);

} */	
/* else
{ */
	pthread_mutex_lock(philo->left_fork);
			ph_print_log(phx, philo, 0);
/* 	usleep(10); */
	pthread_mutex_lock(philo->right_fork);
			ph_print_log(phx, philo, 0);
/* } */
/* 		if (*(philo->right_fork_free) == 1 && *(philo->left_fork_free) == 1)
		{
			*(philo->right_fork_free) = 0; */
/* 					pthread_mutex_lock(&phx->print_mutex);
					printf("%ld %d got my right fork (%p)\n", ph_current_time_msec() - phx->time_start_msec, philo->id, philo->right_fork);
					pthread_mutex_unlock(&phx->print_mutex); */
/* 			*(philo->left_fork_free) = 0; */
/* 					pthread_mutex_lock(&phx->print_mutex);
					printf("%ld %d got my left fork (%p)\n", ph_current_time_msec() - phx->time_start_msec, philo->id, philo->left_fork);
					pthread_mutex_unlock(&phx->print_mutex); */
//			philo->status = 1;
			ph_eat(phx, philo);
/* 			return ;
		} */
/* 		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork); */
}


void *ph_life(void *arg)
{
	t_ph_philo *philo;
	t_ph_vars *phx;

	philo = arg;
	phx = philo->ph_vars;

	while (!(phx->all_init))
		usleep (3);
	if (!(philo->id % 2))
		ph_prec_msleep(phx->time_to_eat - (1));
	while (1)
	{
		if (phx->someone_died == 1)
			break ;
		ph_cyclus(phx, philo);
		if (philo->exitcode == 1 || philo->status == 3)
			break ;
	}
	return NULL;
}
