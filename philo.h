/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:36:39 by skydogzz          #+#    #+#             */
/*   Updated: 2025/02/07 00:36:40 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	t_data				*data;
}						t_philo;

struct					s_data
{
	int					number_of_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					meals_required;
	int					simulation_end;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		simulation_mutex;
	t_philo				*philos;
};

//
// Fonctions utilitaires
//
long long				get_time_in_ms(void);
void					msleep(long long ms);
void					print_status(t_data *data, int id, char *msg);

//
// Fonctions d'initialisation et de parsing des arguments
//
int						parse_args(int argc, char **argv, t_data *data);
int						init_data(t_data *data);

//
// Routines pour les threads
//
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);

#endif
