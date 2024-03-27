/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:27:55 by abennar           #+#    #+#             */
/*   Updated: 2024/03/19 06:03:47 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	argv++;
	if (!parce(argc, argv))
	{
		if (!init_data(argv, &table))
		{
			if (!s_threads(table))
			{
				return (0);
			}
		}
	}
	return (1);
}
