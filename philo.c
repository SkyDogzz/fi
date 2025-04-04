/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:38:18 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/04 19:23:06 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_philo_threads(t_data data)
{
	int			i;

	i = 0;
	while (i < data.number_of_philosophers)
	{
		if (pthread_create(&(data.philos[i].thread), NULL, philosopher_routine,
				(void *)&(data.philos[i])) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	return (true);
}

static bool	init_monitor_thread(t_data data)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, (void *)&data) != 0)
	{
		printf("Error creating monitor thread\n");
		return (false);
	}
	pthread_join(monitor, NULL);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	if (!init_philo_threads(data))
		return (1);
	if (!init_monitor_thread(data))
		return (1);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&(data.forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data.print_mutex));
	pthread_mutex_destroy(&(data.simulation_mutex));
	free(data.forks);
	free(data.philos);
	return (0);
}
