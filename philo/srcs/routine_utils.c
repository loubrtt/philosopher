/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:34:13 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/20 15:10:49 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	if (!safe_check_someone_died(philo->data))
	{
		print_status(philo, "is eating");
		philo->last_meal = what_time(philo);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->data->eating_mutex);
		philo->nb_of_meal++;
		pthread_mutex_unlock(&philo->data->eating_mutex);
		if (philo->nb_of_meal == philo->data->nb_of_time_eating)
		{
			pthread_mutex_lock(&philo->data->finished_mutex);
			philo->data->all_philo_eat++;
			pthread_mutex_unlock(&philo->data->finished_mutex);
		}
	}
}

void	sleeping(t_philo *philo)
{
	if (!safe_check_someone_died(philo->data))
	{
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
}

int	locking(t_philo *philo)
{
	if (!safe_check_someone_died(philo->data) && philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else if (!safe_check_someone_died(philo->data))
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		philo->last_meal = what_time(philo);
	}
	return (0);
}

void	unlocking(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	wake_up(t_philo *philo)
{
	long long	time_to_think;

	if (safe_check_someone_died(philo->data))
		return ;
	time_to_think = (philo->data->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->data->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_status(philo, "is thinking");
	usleep(time_to_think * 1000);
}
