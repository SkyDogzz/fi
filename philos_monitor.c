/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:49:31 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/09 00:34:59 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_philo_solo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		print_status(data, philo->id, "has taken a fork");
		msleep(data->time_to_die);
		pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		return (true);
	}
	return (false);
}

static void	whos_gonna_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id != data->number_of_philosophers)
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
}

static bool	am_i_finished(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->meals_required != -1 && philo->meals_eaten
		>= data->meals_required)
	{
		pthread_mutex_lock(&(data->simulation_mutex));
		philo->finished = true;
		pthread_mutex_unlock(&(data->simulation_mutex));
		return (true);
	}
	return (false);
}

static bool	loop(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_simulation_ended(data))
		return (false);
	if (is_philo_solo(philo))
		return (false);
	whos_gonna_eat(philo);
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
	print_status(data, philo->id, "is sleeping");
	msleep(data->time_to_sleep);
	print_status(data, philo->id, "is thinking");
	if (am_i_finished(philo))
		return (false);
	return (true);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
	{
		print_status(data, philo->id, "is thinking");
		usleep(data->time_to_eat * 0.8 * 1000);
	}
	else if (data->number_of_philosophers % 2 != 0
		&& philo->id == data->number_of_philosophers)
		print_status(data, philo->id, "is thinking");
	while (1)
		if (!loop(philo))
			break ;
	return (NULL);
}
