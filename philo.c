/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:38:18 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/10 18:40:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_yapper(t_data *data)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, (void *)data) != 0)
	{
		printf("Error creating monitor thread\n");
		return (false);
	}
	pthread_join(monitor, NULL);
	return (true);
}

bool	create_philo_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, philosopher_routine,
				(void *)&(data->philos[i])) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (false);
		}
		i++;
	}
	return (true);
}

void	join_philo_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->simulation_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	if (!create_philo_thread(&data))
		return (1);
	if (!init_yapper(&data))
		return (1);
	join_philo_thread(&data);
	destroy_mutex(&data);
	free(data.forks);
	free(data.philos);
	return (0);
}

/*#!/bin/bash*/
/*# Ce script lance x fois la commande ./philo 5 800 200 200 7 */
/*# et stocke chaque sortie dans le dossier "log" :*/
/*# - Un fichier logX pour chaque exécution*/
/*# - Un fichier "log" cumulant toutes les sorties*/
/*# 🚀💾*/
/**/
/*# Vérifier que l'utilisateur a fourni le nombre d'exécutions*/
/*if [ "$#" -ne 1 ]; then*/
/*    echo "Utilisation : $0 nombre_d_execution 🔢"*/
/*    exit 1*/
/*fi*/
/**/
/*nombre_exec=$1*/
/**/
/*# Création du dossier "log" s'il n'existe pas 🚧*/
/*if [ ! -d "log" ]; then*/
/*    mkdir log*/
/*fi*/
/**/
/*# Réinitialiser le fichier global et afficher un message de démarrage 🎬*/
/*echo "=== Début des exécutions === 🏁" > log/log*/
/**/
/*# Boucle de 1 à nombre_exec pour lancer les commandes*/
/*for (( i=1; i<=nombre_exec; i++ )); do*/
/*    echo "Exécution numéro $i 🚀" | tee -a log/log*/
/*    # Exécution de la commande et stockage dans "log/logX"*/
/*    ./philo 5 800 200 200 7 > "log/log$i"*/
/*    # Ajout de la sortie du fichier logX dans le log global*/
/*    cat "log/log$i" | tee -a log/log*/
/*    echo "-------------------------- 🔻" | tee -a log/log*/
/*done*/
/**/
/*echo "=== Exécutions terminées 🎉 ===" | tee -a log/log*/

