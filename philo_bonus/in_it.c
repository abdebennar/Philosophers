/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:04:58 by abennar           #+#    #+#             */
/*   Updated: 2024/03/22 22:35:32 by abennar          ###   ########.fr       */
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

static void	sem_in_it(t_table *table)
{
	int	i;

	i = -1;
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal");
	sem_unlink("/kill");
	sem_unlink("/data_ctl");
	table->forks = sem_open("/forks", O_CREAT, 0644, table->p_num);
	table->write = sem_open("/write", O_CREAT, 0644, 1);
	table->meal = sem_open("/meal", O_CREAT, 0644, 1);
	table->kill = sem_open("/kill", O_CREAT, 0644, table->p_num);
	table->data_ctl = sem_open("/data_ctl", O_CREAT, 0644, 1);
	while (++i < table->p_num)
		sem_wait(table->kill);
}

static int	proc_init(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->p_num);
	if (!table->philo)
		return (1);
	while (i < table->p_num)
	{
		table->philo[i].meals = table->meals;
		table->philo[i].done = false;
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		i++;
	}
	return (0);
}

int	init_data(char **argv, t_table **table)
{
	*table = malloc(sizeof(t_table));
	if (!(*table))
		return (1);
	(*table)->st_op = false;
	cnv_args(argv, *table);
	sem_in_it(*table);
	if (proc_init(*table))
	{
		free(*table);
		return (1);
	}
	return (0);
}
