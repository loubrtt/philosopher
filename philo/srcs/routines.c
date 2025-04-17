/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/26 13:42:08 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/26 13:42:08 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine_for_one(t_philo *philo)
{
	printf("%d ms = Philo %d se reveille et pense ...\n",
		what_time(philo), philo->philo_id);
	usleep(philo->data->time_to_die * 1000);
	printf("%d ms = Philo %d est mort\n", what_time(philo),
		philo->philo_id);
	pthread_mutex_lock(&philo->data->someone_dead);
	philo->data->someone_died++;
	pthread_mutex_unlock(&philo->data->someone_dead);
	return (NULL);
}

int	what_time(t_philo *philo)
{
	int	time;
	int	result;

	time = get_time_in_ms();
	result = time - philo->data->time_stamp;
	return (result);
}

void	*routine_without_goal(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		wake_up(philo);
	while (!safe_check_someone_died(philo->data))
	{
		if (is_dead(philo))
			break ;
		if (locking(philo))
			break ;
		if (is_dead(philo))
		{
			unlocking(philo);
			break ;
		}
		eating(philo);
		unlocking(philo);
		sleeping(philo);
		wake_up(philo);
		if (is_dead(philo))
			break ;
	}
	return (NULL);
}

void	*routine_with_goal(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		wake_up(philo);
	while (!safe_check_someone_died(philo->data)
		&& (safe_check_all_philo_eat(philo->data)))
	{
		if (is_dead(philo))
			break ;
		if (locking(philo))
			break ;
		if (is_dead(philo))
		{
			unlocking(philo);
			break ;
		}
		eating(philo);
		unlocking(philo);
		sleeping(philo);
		wake_up(philo);
		if (is_dead(philo))
			break ;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = what_time(philo);
	if (philo->data->nb_of_philosophers == 1)
		return (routine_for_one(philo));
	if (philo->data->nb_of_time_eating != -1)
		routine_with_goal(philo);
	else
		routine_without_goal(philo);
	return (NULL);
}
