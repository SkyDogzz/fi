/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:38:44 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/04 18:46:53 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_someone_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&(data->simulation_mutex));
		if (!data->simulation_end && (get_time_in_ms()
				- data->philos[i].last_meal) > data->time_to_die)
		{
			print_status(data, data->philos[i].id, "died");
			data->simulation_end = 1;
			pthread_mutex_unlock(&(data->simulation_mutex));
			return (true);
		}
		pthread_mutex_unlock(&(data->simulation_mutex));
		i++;
	}
	return (false);
}

static bool	are_everyone_finished(t_data *data)
{
	int	i;
	int	finished_count;

	finished_count = 0;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&(data->simulation_mutex));
		if (data->philos[i].meals_eaten >= data->meals_required)
			finished_count++;
		pthread_mutex_unlock(&(data->simulation_mutex));
		i++;
	}
	if (finished_count == data->number_of_philosophers)
	{
		pthread_mutex_lock(&(data->simulation_mutex));
		data->simulation_end = 1;
		pthread_mutex_unlock(&(data->simulation_mutex));
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (is_someone_dead(data))
			return (NULL);
		if (data->meals_required != -1 && are_everyone_finished(data))
			return (NULL);
		usleep(1);
	}
	return (NULL);
}
