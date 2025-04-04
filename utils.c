/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:15:57 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/04 18:37:14 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time_in_ms);
}

void	msleep(long long ms)
{
	long long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < ms)
		usleep(100);
}
