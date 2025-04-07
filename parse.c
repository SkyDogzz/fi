/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:48:05 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/07 23:39:00 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parse_args1(char **argv, t_data *data)
{
	if (!strict_atoi(argv[1], &data->number_of_philosophers)
		|| data->number_of_philosophers <= 0)
	{
		printf("Erreur: number_of_philosophers invalide 🚫\n");
		return (false);
	}
	if (!strict_atoll(argv[2], &data->time_to_die) || data->time_to_die < 1)
	{
		printf("Erreur: time_to_die invalide 🚫\n");
		return (false);
	}
	if (!strict_atoll(argv[3], &data->time_to_eat) || data->time_to_eat < 1)
	{
		printf("Erreur: time_to_eat invalide 🚫\n");
		return (false);
	}
	if (!strict_atoll(argv[4], &data->time_to_sleep) || data->time_to_sleep < 1)
	{
		printf("Erreur: time_to_sleep invalide 🚫\n");
		return (false);
	}
	return (true);
}

bool	parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [meals_required]\n", argv[0]);
		return (false);
	}
	if (!parse_args1(argv, data))
		return (false);
	if (argc == 6)
	{
		if (!strict_atoi(argv[5], &data->meals_required)
			|| data->meals_required < 1)
		{
			printf("Erreur: meals_required invalide 🚫\n");
			return (false);
		}
	}
	else
		data->meals_required = -1;
	return (true);
}
