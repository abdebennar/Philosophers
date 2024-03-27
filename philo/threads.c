/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:38:05 by abennar           #+#    #+#             */
/*   Updated: 2024/03/21 22:15:30 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitoring(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->p_num && !table->st_op)
		{
			pthread_mutex_lock(&table->meal);
			if (((long)(get_time() - table->philo[i].lst_eat) > table->t_die)
				&& !get_bool(table, &table->philo[i].done))
			{
				message(&table->philo[i], DEAD);
				set_bool(table, &table->st_op, true);
			}
			pthread_mutex_unlock(&table->meal);
			i++;
		}
		i = 0;
		while (get_bool(table, &table->philo[i].done)
			&& !get_bool(table, &table->st_op))
			i++;
		if (get_bool(table, &table->st_op) || i == table->p_num)
			break ;
	}
	return (0);
}

int	s_threads(t_table *table)
{
	int	i;

	i = 0;
	table->start = get_time();
	while (i < table->p_num)
	{
		table->philo[i].lst_eat = get_time();
		if (pthread_create(&table->philo[i].id_t, NULL,
				rotine, &(table->philo[i])))
			return (1);
		i++;
	}
	monitoring(table);
	join__exit(table);
	return (0);
}
