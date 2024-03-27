/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:19:03 by abennar           #+#    #+#             */
/*   Updated: 2024/03/22 04:01:19 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define THINK  "is thinking\n"
# define EAT    "is eating\n"
# define SLEEP  "is sleeping\n"
# define T_FORK "has taken a fork\n"
# define DEAD   "died\n"

typedef struct s_error
{
	bool	args;
	bool	rang;
	bool	cxms;
	bool	len;
	bool	pos;
	bool	digt;
}				t_error;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pid_t			pid;
	_Atomic long	lst_eat;
	int				id;
	int				meals;
	_Atomic bool	done;
	pthread_t		monitor;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	int				p_num;
	int				meals;
	long			t_die;
	long			t_slp;
	long			t_eat;
	_Atomic bool	st_op;
	bool			inf_meal;
	long			start;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*meal;
	sem_t			*kill;
	sem_t			*data_ctl;
	t_philo			*philo;
}				t_table;

int				parce(int argc, char **argv);
long			ft_atol(const char *str);
int				ft_strlen(const char *str);
int				init_data(char **argv, t_table **table);
int				start_proc(t_table *table);
void			message(t_philo *philo, char *status);
unsigned long	get_time(void);
void			ft_sleep(unsigned int slp, t_table *table);
bool			get_bool(t_table *table, bool *b);
void			set_bool(t_table *table, bool *b, bool v);

#endif