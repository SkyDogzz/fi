/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:51:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/04 18:51:50 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_data *data, int id, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&(data->print_mutex));
	timestamp = get_time_in_ms() - data->start_time;
	if (!data->simulation_end)
		printf("%lld %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(&(data->print_mutex));
}
