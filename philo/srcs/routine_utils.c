/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:34:13 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/16 21:01:53 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	if (!safe_check_someone_died(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d is eating\n", what_time(philo), philo->philo_id);
		philo->last_meal = what_time(philo);
		pthread_mutex_unlock(&philo->data->print_mutex);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->data->eating_mutex);
		philo->nb_of_meal++;
		pthread_mutex_unlock(&philo->data->eating_mutex);
		pthread_mutex_lock(&philo->data->finished_mutex);
		if (philo->nb_of_meal == philo->data->nb_of_time_eating)
			philo->data->all_philo_eat++;
		pthread_mutex_unlock(&philo->data->finished_mutex);
	}
}

void	sleeping(t_philo *philo)
{
	if (!safe_check_someone_died(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d is sleeping\n", what_time(philo), philo->philo_id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		usleep(philo->data->time_to_sleep * 1000);
	}
}

int	locking(t_philo *philo)
{
	if (!safe_check_someone_died(philo->data) && philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d has taken a fork\n", what_time(philo), philo->philo_id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d has taken a fork\n", what_time(philo), philo->philo_id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else if (!safe_check_someone_died(philo->data))
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d has taken a fork\n", what_time(philo), philo->philo_id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d has taken a fork\n", what_time(philo), philo->philo_id);
		philo->last_meal = what_time(philo);
		pthread_mutex_unlock(&philo->data->print_mutex);
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
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%d %d is thinking\n", what_time(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(time_to_think * 1000, philo);
}
