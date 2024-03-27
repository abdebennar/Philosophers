/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:30:45 by abennar           #+#    #+#             */
/*   Updated: 2024/03/21 20:46:53 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_atol(const char *str)
{
	int				sign;
	long			number;

	number = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return ((long)(sign * number));
}

void	message(t_philo *philo, char *status)
{
	sem_wait(philo->table->write);
	if (!philo->table->st_op)
	{
		printf("%ld %d %s", get_time() - philo->table->start,
			philo->id, status);
	}
	sem_post(philo->table->write);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(unsigned int slp, t_table *table)
{
	unsigned long	start;

	start = get_time();
	while (!table->st_op)
	{
		if (get_time() - start >= slp)
			break ;
		usleep(table->p_num * 2);
	}
}
