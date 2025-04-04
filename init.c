/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:14:48 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/04 18:33:28 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_simple_data(t_data *data)
{
	data->simulation_end = 0;
	data->start_time = get_time_in_ms();
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (false);
	return (true);
}

static bool	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(data->simulation_mutex), NULL) != 0)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (false);
	return (true);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->number_of_philosophers;
		i++;
	}
}

bool	init_data(t_data *data)
{
	if (!init_simple_data(data))
		return (false);
	if (!init_mutex(data))
		return (false);
	init_philos(data);
	return (true);
}
