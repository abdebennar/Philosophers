/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:31 by abennar           #+#    #+#             */
/*   Updated: 2024/03/21 20:44:22 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cnv_args(char **args, t_table *table)
{
	table->p_num = ft_atol(args[0]);
	table->t_die = ft_atol(args[1]);
	table->t_eat = ft_atol(args[2]);
	table->t_slp = ft_atol(args[3]);
	if (args[4] != NULL)
	{
		table->meals = ft_atol(args[4]);
		table->inf_meal = false;
	}
	else
		table->inf_meal = true;
}

static int	threads_init(t_table *table)
{
	int	i;

	i = 0;
	table->philo = (t_philo *)malloc(table->p_num * sizeof(t_philo));
	if (!table->philo)
		return (1);
	table->st_op = false;
	while (i < table->p_num)
	{
		table->philo[i].table = table;
		table->philo[i].meals = table->meals;
		table->philo[i].id = i + 1;
		table->philo[i].f_fork = i;
		table->philo[i].s_fork = (i + 1) % table->p_num;
		table->philo[i].done = false;
		i++;
	}
	return (0);
}

static int	mutexes_init(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(table->p_num * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (1);
	while (i < table->p_num)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->write, NULL))
		return (1);
	if (pthread_mutex_init(&table->meal, NULL))
		return (1);
	if (pthread_mutex_init(&table->data_ctl, NULL))
		return (1);
	return (0);
}

int	init_data(char **argv, t_table **table)
{
	*table = malloc(sizeof(t_table));
	if (!*table)
		return (1);
	cnv_args(argv, *table);
	if (mutexes_init(*table))
	{
		ft_free(*table, NULL, NULL);
		return (1);
	}
	if (threads_init(*table))
	{
		ft_free(*table, (*table)->forks, NULL);
		return (1);
	}
	return (0);
}
