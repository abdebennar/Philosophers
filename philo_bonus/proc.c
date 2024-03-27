/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:42:58 by abennar           #+#    #+#             */
/*   Updated: 2024/03/22 04:01:57 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->meal);
	sem_close(table->kill);
	sem_close(table->write);
	sem_close(table->data_ctl);
	free(table->philo);
	free(table);
}

static void	eating(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(table->forks);
	message(philo, T_FORK);
	sem_wait(table->forks);
	message(philo, T_FORK);
	sem_wait(table->meal);
	philo->lst_eat = get_time();
	message(philo, EAT);
	philo->meals--;
	sem_post(table->meal);
	ft_sleep(table->t_eat, table);
	sem_post(table->forks);
	sem_post(table->forks);
}

static void	*monitoring(void *param)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->table->meal);
		if ((long)get_time() - philo->lst_eat > philo->table->t_die
			&& !philo->done)
		{
			message(philo, DEAD);
			sem_wait(philo->table->write);
			philo->table->st_op = true;
			while (++i < philo->table->p_num)
				sem_post(philo->table->kill);
		}
		sem_post(philo->table->meal);
		if (philo->table->st_op)
			break ;
	}
	return (NULL);
}

static void	*rotine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->id % 2 && philo->table->p_num > 1)
		ft_sleep(table->t_die / table->p_num, table);
	pthread_create(&philo->monitor, NULL, monitoring, philo);
	while (!table->st_op)
	{
		if (philo->meals > 0 || table->inf_meal)
		{
			eating(philo);
			message(philo, SLEEP);
			ft_sleep(table->t_slp, table);
			message(philo, THINK);
		}
		else if (!table->inf_meal && philo->meals <= 0)
		{
			philo->done = true;
			sem_post(philo->table->kill);
			while (1)
			{
			}
		}
	}
	return (NULL);
}

int	start_proc(t_table *table)
{
	int	i;

	i = 0;
	table->start = get_time();
	while (i < table->p_num)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == 0)
		{
			table->philo[i].lst_eat = get_time();
			rotine(&table->philo[i]);
			exit(0);
		}
		i++;
	}
	i = -1;
	while (++i < table->p_num)
		sem_wait(table->kill);
	i = -1;
	while (++i < table->p_num)
		kill(table->philo[i].pid, SIGINT);
	clean(table);
	return (0);
}
