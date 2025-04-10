/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:51:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/09 00:35:05 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_ended(t_data *data)
{
	pthread_mutex_lock(&(data->simulation_mutex));
	if (data->simulation_end)
	{
		pthread_mutex_unlock(&(data->simulation_mutex));
		return (true);
	}
	pthread_mutex_unlock(&(data->simulation_mutex));
	return (false);
}

void	print_status(t_data *data, int id, const char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&(data->print_mutex));
	timestamp = get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&(data->simulation_mutex));
	if (!data->simulation_end)
		printf("%lld %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(&(data->simulation_mutex));
	pthread_mutex_unlock(&(data->print_mutex));
}
