#include "../header/philosophers.h"

/* ************************************************************************** */
// MAIN
/* ************************************************************************** */

// todo: 
// do i have to check if time ags given are > 0? what happens if = 0?
// edge case 0 or 1 philo covered?
// destroyed and freed all mutexes?
// how avoid philos printng stuff at same timestamp? -> now i will try to cut to ms only at the moment of printnig to propagate less errors in the conversions
void ph_init(t_ph_vars *phx)
{
	struct timeval tvx;

	gettimeofday(&tvx, NULL);
	phx->time_start_msec = 	(tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	phx->nth_philo = NULL;
	pthread_mutex_init(&phx->print_mutex, NULL);
	phx->print_mutex_islocked = 0;
	phx->someone_died = 0;
	pthread_mutex_init(&phx->someone_died_mutex, NULL);
	pthread_mutex_init(&phx->print_mutex_islocked_lock, NULL);
	phx->all_init = 0;
}

int main(int argc, char **argv)
{
	t_ph_vars	phx;
	int n_error;

	if (ph_parse(&phx, argc, argv) != 0)
		return (1);
	ph_init(&phx);
	n_error = ph_set_forks(&phx);
	if (n_error)
	{
		ph_free(&phx, -1, 0);
		return (3);
	}
	n_error = ph_simulation(&phx);
	if (n_error)
	{
		ph_free(&phx, -1, n_error);
		return (4);
	}
	ph_free(&phx, -1, -1);
	return (0);
}
