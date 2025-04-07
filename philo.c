/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:38:18 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/07 17:36:01 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	pthread_t	monitor;

	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		if (pthread_create(&(data.philos[i].thread), NULL, philosopher_routine,
				(void *)&(data.philos[i])) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, (void *)&data) != 0)
	{
		printf("Error creating monitor thread\n");
		return (1);
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&(data.forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data.simulation_mutex));
	pthread_mutex_destroy(&(data.print_mutex));
	free(data.forks);
	free(data.philos);
	return (0);
}
