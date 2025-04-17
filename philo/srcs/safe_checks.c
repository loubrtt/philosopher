/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:22:56 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/16 19:37:59 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	safe_check_someone_died(t_global *data)
{
	int	val;

	pthread_mutex_lock(&data->someone_dead_check);
	val = data->someone_died;
	pthread_mutex_unlock(&data->someone_dead_check);
	return (val);
}

int	safe_check_all_philo_eat(t_global *data)
{
	int	result;

	if (data->nb_of_time_eating == -1)
		return (1);
	pthread_mutex_lock(&data->finished_mutex);
	result = data->all_philo_eat < data->nb_of_philosophers;
	pthread_mutex_unlock(&data->finished_mutex);
	return (result);
}

int	safe_check_if_philo_died(t_philo *philo)
{
	long long	now;
	int			last_meal;
	int			result;

	now = what_time(philo);
	pthread_mutex_lock(&philo->data->is_philo_dead);
	last_meal = now - philo->last_meal;
	result = philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->is_philo_dead);
	if (last_meal > result)
		return (1);
	return (0);
}
