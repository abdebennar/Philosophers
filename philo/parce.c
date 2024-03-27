/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:29:46 by abennar           #+#    #+#             */
/*   Updated: 2024/03/22 23:19:42 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_errors(t_error error)
{
	if (error.args)
		printf("Error: Insufficient arguments."
			" Please provide the required input.\n");
	if (error.digt)
		printf("Error: Invalid input. Non-digit"
			" characters are not allowed.\n");
	if (error.rang || error.len)
		printf("Error: Input exceeds the limit of threads or time."
			" Please provide a smaller value.\n");
	if (error.pos)
		printf("Error: Positive numbers are not allowed."
			" Please provide a non-positive value.\n");
	if (!(error.args || error.digt || error.rang || error.len || error.pos))
		return (0);
	return (1);
}

static void	valid_input(char **args, t_error *error)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (ft_strlen(args[i]) > 10 || ft_strlen(args[i]) == 0)
			error->len = true;
		j = 0;
		while (args[i][j])
		{
			if ((args[i][j] == '-' || args[i][j] == '+') && j == 0)
			{
				if (args[i][j] == '-')
					error->pos = true;
				j++;
			}
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				error->digt = true;
			j++;
		}
		i++;
	}
}

int	parce(int argc, char **argv)
{
	t_error	error;

	error.args = false;
	error.digt = false;
	error.rang = false;
	error.len = false;
	error.pos = false;
	if (argc > 6 || argc < 5)
		error.args = true;
	else
	{
		valid_input(argv, &error);
		if (ft_atol(argv[0]) > 10240)
			error.rang = true;
	}
	return (check_errors(error));
}
