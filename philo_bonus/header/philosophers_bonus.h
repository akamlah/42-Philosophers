/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:37:31 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 19:45:17 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# define PHB_SEM_FORKS	"/phb_sem_forks"
# define PHB_SEM_PRINT	"/phb_sem_print"

/* ************************************************************************** */

typedef struct s_ph_philo
{
	int					id;
	int					times_eaten;
	long				tsmp_msec;
	long				tsmp_lastmeal_msec;
	int					pid;
	int					ate_enough;
	void				*ph_vars;
	sem_t				*sem_forks;
	sem_t				*sem_print;
	struct s_ph_philo	*prev;
}						t_ph_philo;

typedef struct s_ph_vars
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				prec_sleep_interval;
	long			time_start_msec;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	pthread_t		death;
	t_ph_philo		*nth_philo;
}					t_ph_vars;

/* ************************************************************************** */

int			ph_parse(t_ph_vars *phbx, int argc, char **argv);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);

// cycle
int			ph_prec_msleep(long tv_tosleep_msec, int interval);
void		phb_print_log(t_ph_vars *phbx, t_ph_philo *philo, int msgnr);
void		phb_philos_life(t_ph_vars *phbx, t_ph_philo *philo);
void		*phb_death(void *arg);

// init
int			phb_init(t_ph_vars *phbx);
t_ph_philo	*phb_new_philo(t_ph_vars *phbx, int id);
int			phb_simulation(t_ph_vars *phbx);
int			phb_philo(t_ph_vars *phbx, int id);

// todo:
void		ph_free(t_ph_vars *phbx, int forks, int philos);

/* ************************************************************************** */

#endif
