/* ************************************************************************** */

#ifndef _PHILO_H_
# define _PHILO_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

/* ************************************************************************** */
typedef struct			s_ph_philo
{
	int					id;
	int					status;
	int					times_eaten;
	long				tsmp_msec;
	long				tsmp_lastmeal_msec;
	int					*left_fork_free;
	int					*right_fork_free;
	int					has_lfork;
	int					has_rfork;
	int					exitcode;
	pthread_mutex_t		exit_mtx;
	void				*ph_vars;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_ph_philo	*prev;
	pthread_t			philo_thread;
}						t_ph_philo;
typedef struct		s_ph_vars
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				someone_died;
	int				print_mutex_islocked;
	long			time_start_msec;
	pthread_mutex_t	*forks;
	pthread_mutex_t	someone_died_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	print_mutex_islocked_lock;
	t_ph_philo		*nth_philo;
	pthread_t		death; // TO DO 
	int all_init;
		int				*forks_status;
}					t_ph_vars;

/* ************************************************************************** */

// parser
int		ph_parse(t_ph_vars *phx, int argc, char **argv);

// simulation
int		ph_set_forks(t_ph_vars *phx);
int		ph_simulation(t_ph_vars *phx);

// philo
int		ph_philo(t_ph_vars *phx, int id);

t_ph_philo *ph_new_philo(t_ph_vars *phx, int id);
// routine
void	*ph_life(void *arg);

// free
void	ph_free(t_ph_vars *phx, int forks, int philos);

// time
long	ph_current_time_msec();
int		ph_prec_msleep(long tv_tosleep_msec);

// other utils
int		ft_atoi(const char *str);
size_t	ft_strlen (const char *s);


/* ************************************************************************** */

#endif
