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

int	what_time(t_philo *philo)
{
	int time;
	int result;

	time = get_time_in_ms();
	result = time - philo->data->time_stamp;
	if (result < 100)
		return (result);
	else
		return (result / 1000);
}

void	*routine_without_goal(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_in_ms();
	while (!philo->data->someone_died)
	{
		printf("%d sec = Philosophe %d se reveille et pense ...\n",
			what_time(philo), philo->philo_id);
		if (is_dead(philo))
			break ;
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("%d sec = Philo %d mange\n", what_time(philo), philo->philo_id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->last_meal = get_time_in_ms();
		philo->nb_of_meal++;
		printf("%d sec = Philo %d dort\n", what_time(philo), philo->philo_id);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_in_ms();
	if (philo->data->nb_of_philosophers == 1)
	{
		printf("%d sec = Philosophe %d se reveille et pense ...\n",
			what_time(philo), philo->philo_id);
		usleep(philo->data->time_to_die * 1000);
		printf("%d sec = Philo %d est mort\n", what_time(philo),
			philo->philo_id);
		philo->data->someone_died++;
		return (NULL);
	}
	if (philo->data->nb_of_time_eating != -1)
	{
		while (!philo->data->someone_died
			&& (philo->nb_of_meal < philo->data->nb_of_time_eating))
		{
			if (is_dead(philo))
			{
				printf("%d sec = Philo %d est mort\n", what_time(philo),
					philo->philo_id);
				break ;
			}
			printf("%d sec = Philosophe %d se reveille et pense ...\n",
				what_time(philo), philo->philo_id);
			if (is_dead(philo))
			{
				printf("%d sec = Philo %d est mort\n", what_time(philo),
					philo->philo_id);
				break ;
			}
			pthread_mutex_lock(philo->left_fork);//rentre dans le mutex
			pthread_mutex_lock(philo->right_fork);
			philo->last_meal = get_time_in_ms();//marqueur temps mutex
			printf("%d sec = Philo %d mange\n", what_time(philo),
				philo->philo_id);
			usleep(philo->data->time_to_eat * 1000);
			pthread_mutex_unlock(philo->right_fork);//sortie du mutex
			pthread_mutex_unlock(philo->left_fork);
			philo->nb_of_meal++;
			printf("%d sec = Philo %d dort\n", what_time(philo),
				philo->philo_id);
			usleep(philo->data->time_to_sleep * 1000);//sleep
			if (is_dead(philo))
			{
				printf("%d sec = Philo %d est mort\n", what_time(philo),
					philo->philo_id);
				break ;
			}
		}
	}
	else
		routine_without_goal(arg);
	return (NULL);
}
