#include "../header/philosophers.h"

/*
	returns elapsed time (as in <sys/time.h>) in milliseconds
	or -1 on error.
*/
/*
long ph_current_time_msec(void)
{
	struct timeval tvx;

	gettimeofday(&tvx, NULL);
	{
		perror("Error gettimeofday");
		return (-1);
	}
	return ((tvx.tv_usec / 1000) + (tvx.tv_sec * 1000));
}
 */
/*
	The usleep() function suspends execution of the calling thread
	for (at least) usec microseconds. The sleep may be lengthened
	slightly by any system activity or by the time spent processing
	the call or by the granularity of system timers.
*/
int	ph_prec_msleep(long tv_tosleep_msec)
{
	struct timeval	timeofday;
	long		start_time;
	long		timer;

	start_time = 0;
	timer = 0;
	gettimeofday(&timeofday, NULL);
	start_time = (timeofday.tv_usec / 1000) + (timeofday.tv_sec * 1000);
	while (timer < tv_tosleep_msec)
	{
		usleep(100);
		gettimeofday(&timeofday, NULL);
		timer = (timeofday.tv_usec / 1000) + (timeofday.tv_sec * 1000) - start_time;
	}
/* 	long tv_start_msec;
	long now;
	
	tv_start_msec = ph_current_time_msec();
	now = ph_current_time_msec();
	while (1)
	{
		if (now - tv_start_msec >= tv_tosleep_msec)
			break ;
		usleep(10);
		now = ph_current_time_msec();
	} */
	return 0;
}