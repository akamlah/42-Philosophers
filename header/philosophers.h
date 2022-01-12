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
	int					times_eaten;
	long				tsmp_msec;
	long				tsmp_lastmeal_msec;
	int					exitcode;
	int					ate_enough;
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
	int				all_philos_created;
	int				prec_sleep_interval;
	long			time_start_msec;
	pthread_mutex_t	*forks;
	pthread_mutex_t	someone_died_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		death;
	t_ph_philo		*nth_philo;
}					t_ph_vars;

/* ************************************************************************** */

int			ph_parse(t_ph_vars *phx, int argc, char **argv);
int			ft_atoi(const char *str);
size_t		ft_strlen (const char *s);
void		ph_free(t_ph_vars *phx, int forks, int philos);
int			ph_simulation(t_ph_vars *phx);
int			ph_init(t_ph_vars *phx);
int			ph_init_forks(t_ph_vars *phx);
int			ph_philo(t_ph_vars *phx, int id);
int			ph_prec_msleep(long tv_tosleep_msec, int interval);
void		ph_print_log(t_ph_vars *phx, t_ph_philo *philo, int msgnr);
void		ph_death_log(t_ph_vars *phx, t_ph_philo *philo);

/* ************************************************************************** */

#endif
