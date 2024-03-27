/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:18:51 by abennar           #+#    #+#             */
/*   Updated: 2024/03/22 19:51:25 by abennar          ###   ########.fr       */
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
			if (!start_proc(table))
			{
				return (0);
			}
		}
	}
	return (1);
}
