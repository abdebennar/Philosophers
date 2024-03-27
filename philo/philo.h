/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:28:18 by abennar           #+#    #+#             */
/*   Updated: 2024/03/23 01:15:08 by abennar          ###   ########.fr       */
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
# include <sys/time.h>

# define THINK  "is thinking\n"
# define EAT    "is eating\n"
# define SLEEP  "is sleeping\n"
# define T_FORK "has taken a fork\n"
# define DEAD   "died\n"

typedef struct s_philo	t_philo;

typedef struct s_error
{
	bool	args;
	bool	rang;
	bool	cxms;
	bool	len;
	bool	pos;
	bool	digt;
}				t_error;

typedef struct s_table
{
	int				p_num;
	int				meals;
	long			t_die;
	long			t_slp;
	long			t_eat;
	bool			st_op;
	bool			inf_meal;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
	pthread_mutex_t	data_ctl;
	t_philo			*philo;
}				t_table;

struct s_philo
{
	pthread_t	id_t;
	t_table		*table;
	int			id;
	int			meals;
	long		lst_eat;
	bool		done;
	int			s_fork;
	int			f_fork;
};

void				ft_free(t_table *table, void *forks, void *thread);
void				ft_sleep(unsigned int slp, t_table *table);
int					ft_strlen(const char *str);
long				ft_atol(const char *s);
int					parce(int argc, char **argv);
int					init_data(char **argv, t_table **table);
void				*rotine(void	*param);
void				message(t_philo *philo, char *status);
int					s_threads(t_table *table);
unsigned long		get_time(void);
bool				get_bool(t_table *table, bool *b);
void				set_bool(t_table *table, bool *b, bool v);
void				join__exit(t_table *table);

#endif