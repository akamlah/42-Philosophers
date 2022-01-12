#include "../header/philosophers.h"

/* 	if (gettimeofday(&tvx, NULL))
	{
		perror("Error gettimeofday");
		pthread_mutex_unlock(&phx->print_mutex);
		return ;
	} */
void	ph_print_log(t_ph_vars *phx, t_ph_philo *philo, int msgnr)
{
	char *msg[5] = {"has taken a fork", "is eating", "is sleeping", "is thinking", "died"};
	struct timeval tvx;

	gettimeofday(&tvx, NULL);
	philo->tsmp_msec = ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000)) - phx->time_start_msec;
	pthread_mutex_lock(&phx->print_mutex);
	if (msgnr != 4 && !phx->someone_died && !philo->ate_enough)
		printf("%ld %d %s\n", philo->tsmp_msec, philo->id, msg[msgnr]);
	if (msgnr == 4 && !philo->ate_enough)
		printf("%ld %d %s\n", ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000)) - phx->time_start_msec, philo->id, msg[msgnr]);
	pthread_mutex_unlock(&phx->print_mutex);
}

/*
	The usleep() function suspends execution of the calling thread
	for (at least) usec microseconds. The sleep may be lengthened
	slightly by any system activity or by the time spent processing
	the call or by the granularity of system timers.
	
	need a clock thread if i want to do error handeling, or all ifs kill performance.
*/
int	ph_prec_msleep(long tv_tosleep_msec, int interval)
{
	struct timeval	tvx;
	long			start;
	long			now;
	long			tosleep;

	gettimeofday(&tvx, NULL);
	start = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	now = start;
	tosleep = start + tv_tosleep_msec;
	while (now < tosleep)
	{
		usleep(interval);
		gettimeofday(&tvx, NULL);
		now = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	}
	return 0;
}