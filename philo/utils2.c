/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:33:26 by abennar           #+#    #+#             */
/*   Updated: 2024/03/21 22:14:23 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(t_table *table, bool *b)
{
	pthread_mutex_lock(&table->data_ctl);
	if (*b)
	{
		pthread_mutex_unlock(&table->data_ctl);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&table->data_ctl);
		return (false);
	}
}

void	set_bool(t_table *table, bool *b, bool v)
{
	pthread_mutex_lock(&table->data_ctl);
	*b = v;
	pthread_mutex_unlock(&table->data_ctl);
}

void	ft_sleep(unsigned int slp, t_table *table)
{
	unsigned long	start;

	start = get_time();
	while (!get_bool(table, &table->st_op))
	{
		if (get_time() - start >= slp)
			break ;
		usleep(table->p_num * 3);
	}
}

void	join__exit(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->p_num && table->p_num > 1)
	{
		pthread_join(table->philo[i].id_t, NULL);
		i++;
	}
	ft_free(table, table->forks, table->philo);
}
