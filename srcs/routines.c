/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:42:08 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/26 13:42:08 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine_without_goal(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->someone_died)
	{
		printf("Philosophe %d se reveille et pense ...\n", philo->philo_id);
		if (is_dead(philo))
		{
			printf("philo %d est mort\n", philo->philo_id);
			break ;
		}
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("Philo %d mange\n", philo->philo_id);
		usleep(philo->data->time_to_eat * 1000);
		philo->nb_of_meal++;
		philo->last_meal = get_time_in_ms();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("Philo %d dort\n", philo->philo_id);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_of_time_eating != -1)
	{
		while (!philo->data->someone_died
			&& (philo->nb_of_meal < philo->data->nb_of_time_eating))
		{
			printf("Philosophe %d se reveille et pense ...\n", philo->philo_id);
			if (is_dead(philo))
			{
				printf("philo %d est mort\n", philo->philo_id);
				break ;
			}
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			printf("Philo %d mange\n", philo->philo_id);
			usleep(philo->data->time_to_eat * 1000);
			philo->nb_of_meal++;
			philo->last_meal = get_time_in_ms();
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			if (philo->nb_of_meal >= philo->data->nb_of_time_eating
				&& philo->data->nb_of_time_eating != -1)
			{
				printf("le philo %d a fini sa routine\n", philo->philo_id);
				break ;
			}
			printf("Philo %d dort\n", philo->philo_id);
			usleep(philo->data->time_to_sleep * 1000);
		}
	}
	else
		routine_without_goal(arg);
	return (NULL);
}
