/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:34:13 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/07 15:51:25 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	if (!philo->data->someone_died)
	{
		philo->last_meal = get_time_in_ms();
		printf("%d ms = Philo %d mange\n", what_time(philo), philo->philo_id);
		usleep(philo->data->time_to_eat * 1000);
		philo->nb_of_meal++;
	}
}

void	sleeping(t_philo *philo)
{
	if (!philo->data->someone_died)
	{
		printf("%d ms = Philo %d dort\n", what_time(philo), philo->philo_id);
		usleep(philo->data->time_to_sleep * 1000);
	}
}

void	locking(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

void	unlocking(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	wake_up(t_philo *philo)
{
	if (!philo->data->someone_died)
	{
		printf("%d ms = Philosophe %d se reveille et pense ...\n",
			what_time(philo), philo->philo_id);
	}
}
