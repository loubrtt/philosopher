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
	printf("%d ms = Philosophe %d se reveille et pense ...\n",
		what_time(philo), philo->philo_id);
	usleep(philo->data->time_to_die * 1000);
	printf("%d ms = Philo %d est mort\n", what_time(philo),
		philo->philo_id);
	philo->data->someone_died++;
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
	philo->last_meal = get_time_in_ms();
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{
		wake_up(philo);
		locking(philo);
		if (is_dead(philo))
		{
			unlocking(philo);
			break ;
		}
		eating(philo);
		unlocking(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	*routine_with_goal(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died
		&& (philo->nb_of_meal < philo->data->nb_of_time_eating))
	{
		wake_up(philo);
		locking(philo);
		if (is_dead(philo))
		{
			unlocking(philo);
			break ;
		}
		eating(philo);
		unlocking(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_in_ms();
	if (philo->data->nb_of_philosophers == 1)
		return (routine_for_one(philo));
	if (philo->data->nb_of_time_eating != -1)
		routine_with_goal(philo);
	else
		routine_without_goal(philo);
	return (NULL);
}
