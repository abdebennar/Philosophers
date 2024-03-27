/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:33:02 by abennar           #+#    #+#             */
/*   Updated: 2024/03/21 22:15:24 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->f_fork]);
	message(philo, T_FORK);
	pthread_mutex_lock(&table->forks[philo->s_fork]);
	message(philo, T_FORK);
	pthread_mutex_lock(&table->meal);
	philo->lst_eat = get_time();
	message(philo, EAT);
	philo->meals--;
	pthread_mutex_unlock(&table->meal);
	ft_sleep(table->t_eat, table);
	pthread_mutex_unlock(&table->forks[philo->s_fork]);
	pthread_mutex_unlock(&table->forks[philo->f_fork]);
}

void	*rotine(void	*param)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)param;
	table = philo->table;
	if (philo->id % 2 && table->p_num > 1)
		ft_sleep(table->t_die / table->p_num, table);
	while (!get_bool(table, &table->st_op))
	{
		if (philo->meals > 0 || table->inf_meal)
		{
			eating(philo);
			message(philo, SLEEP);
			ft_sleep(table->t_slp, table);
			message(philo, THINK);
		}
		else if (!table->inf_meal)
		{
			set_bool(table, &philo->done, true);
			break ;
		}
	}
	return (NULL);
}
