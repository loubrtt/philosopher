/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:03:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/26 13:40:41 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	return_function(int i)
{
	if (i == 1)
	{
		printf("Error: Please provide at least");
		printf(" one philosopher as input.\n");
	}
	if (i == 2)
	{
		printf("Error: Please provide at least one");
		printf(" millisecond before dying as input.\n");
	}
	if (i == 3)
	{
		printf("Error: Please provide at least one");
		printf(" millisecond for eating as input.\n");
	}
	if (i == 4)
	{
		printf("Error: Please provide at least one");
		printf(" millisecond for sleep as input.\n");
	}
	return (1);
}

int	parsing_global(t_global *data, char **av)
{
	data->time_stamp = get_time_in_ms();
	data->someone_died = 0;
	data->i = 0;
	data->nb_of_philosophers = ft_atoll(av[1]);
	if (data->nb_of_philosophers < 1)
		data->i = return_function(1);
	data->nb_of_forks = data->nb_of_philosophers;
	data->time_to_die = ft_atoll(av[2]);
	if (data->time_to_die <= 0)
		data->i = return_function(2);
	data->time_to_eat = ft_atoll(av[3]);
	if (data->time_to_eat <= 0)
		data->i = return_function(3);
	data->time_to_sleep = ft_atoll(av[4]);
	if (data->time_to_sleep <= 0)
		data->i = return_function(4);
	if (av[5])
		data->nb_of_time_eating = ft_atoll(av[5]);
	else
		data->nb_of_time_eating = -1;
	if (data->i)
		return (1);
	return (0);
}

int	is_dead(t_philo *philo)
{
	long long	now;

	now = get_time_in_ms();
	if ((now - philo->last_meal) > philo->data->time_to_die)
		return (1);
	return (0);
}
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

int	parsing(t_global *data, t_philo **philo, char **av)
{
	if (parsing_global(data, av))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	if (!data->forks)
		return (1);
	if(init_forks(data->forks, data->nb_of_philosophers))
	{
		free(data->forks);
		return (1);
	}
	*philo = malloc(sizeof(t_philo) * data->nb_of_philosophers);
	if (!*philo)
	{
		free(data->forks);
		return (1);
	}
	return (0);
}
void	free_structs(t_global *data, t_philo *philo)
{
	free(data->forks);
	free(philo);
}
int	main(int ac, char **av)
{
	t_global	data;
	t_philo		*philo;
	int			i;

	i = 0;
	philo = NULL;
	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, &philo, av))
			return (1);
		while (i < data.nb_of_philosophers)
		{
			init_philo(&philo[i], i, &data);
			pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i]));
			i++;
		}
		i = 0;
		while (i < data.nb_of_philosophers)
		{
			pthread_join(philo[i].thread_id, NULL);
			i++;
		}
		free_structs(&data, philo);
	}
	else
		printf("The program needs 4 or 5 arguments\n");
	return (0);
}
