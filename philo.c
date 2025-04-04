/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:38:18 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/04 18:38:55 by tstephan         ###   ########.fr       */
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

bool	parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat \
				time_to_sleep [meals_required]\n", argv[0]);
		return (false);
	}
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	if (data->number_of_philosophers <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0 || (argc == 6
			&& data->meals_required <= 0))
	{
		printf("Invalid arguments\n");
		return (false);
	}
	return (true);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(data->simulation_mutex));
		if (data->simulation_end)
		{
			pthread_mutex_unlock(&(data->simulation_mutex));
			break ;
		}
		pthread_mutex_unlock(&(data->simulation_mutex));
		if (data->number_of_philosophers == 1)
		{
			pthread_mutex_lock(&(data->forks[philo->left_fork]));
			print_status(data, philo->id, "has taken a fork");
			msleep(data->time_to_die);
			pthread_mutex_unlock(&(data->forks[philo->left_fork]));
			break ;
		}
		if (philo->id % 2 == 1)
		{
			pthread_mutex_lock(&(data->forks[philo->left_fork]));
			print_status(data, philo->id, "has taken a fork");
			pthread_mutex_lock(&(data->forks[philo->right_fork]));
			print_status(data, philo->id, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&(data->forks[philo->right_fork]));
			print_status(data, philo->id, "has taken a fork");
			pthread_mutex_lock(&(data->forks[philo->left_fork]));
			print_status(data, philo->id, "has taken a fork");
		}
		pthread_mutex_lock(&(data->simulation_mutex));
		philo->last_meal = get_time_in_ms();
		pthread_mutex_unlock(&(data->simulation_mutex));
		print_status(data, philo->id, "is eating");
		msleep(data->time_to_eat);
		pthread_mutex_lock(&(data->simulation_mutex));
		philo->meals_eaten++;
		pthread_mutex_unlock(&(data->simulation_mutex));
		pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		pthread_mutex_unlock(&(data->forks[philo->right_fork]));
		if (data->meals_required != -1
			&& philo->meals_eaten >= data->meals_required)
			break ;
		print_status(data, philo->id, "is sleeping");
		msleep(data->time_to_sleep);
		print_status(data, philo->id, "is thinking");
	}
	return (NULL);
}

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
	pthread_mutex_destroy(&(data.print_mutex));
	pthread_mutex_destroy(&(data.simulation_mutex));
	free(data.forks);
	free(data.philos);
	return (0);
}
