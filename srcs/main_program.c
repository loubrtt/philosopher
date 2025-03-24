/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:03:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/24 17:39:33 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parsing_global(t_global *data, char **av)
{
	data->i = 0;
	data->nb_of_philosophers = ft_atoll(av[1]);
	if (data->nb_of_philosophers < 1)
	{
		printf("Error: Please provide at least\
		one philosopher as input.\n");
		data->i = 1;
	}
	data->nb_of_forks = data->nb_of_philosophers;
	data->time_to_die = ft_atoll(av[2]);
	if (data->time_to_die <= 0)
	{
		printf("Error: Please provide at least one \
			millisecond before dying as input.\n");
		data->i = 1;
	}
	data->time_to_eat = ft_atoll(av[3]);
	if (data->time_to_eat <= 0)
	{
		printf("Error: Please provide at least one \
			millisecond for eating as input.\n");
		data->i = 1;
	}
	data->time_to_sleep = ft_atoll(av[4]);
	if (data->time_to_sleep <= 0)
	{
		printf("Error: Please provide at least one \
			millisecond for sleep as input.\n");
		data->i = 1;
	}
	data->nb_of_time_eating = ft_atoll(av[5]);
	if (data->nb_of_time_eating <= 0)
	{
		printf("Error: Please provide at least one \
			time for eating as input.\n");
		data->i = 1;
	}
	if (data->i)
		return (1);
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if (philo->nb_of_meal == philo->data->nb_of_time_eating)
		return (NULL);
	while (!philo->data->someone_died && (philo->nb_of_meal < philo->data->nb_of_time_eating))
	{
		printf("Philosophe %d pense ...\n", philo->philo_id);
		pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
		printf("Philo %d mange\n", philo->philo_id);
		usleep(philo->data->time_to_eat * 1000);
		philo->nb_of_meal++;
		printf("philo nb %d nb de repas = %lld\n\n", philo->philo_id, philo->nb_of_meal);
		philo->last_meal = get_time_in_ms();
		pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
		printf("Philo %d dort\n", philo->philo_id);
    	usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

int init_forks(pthread_mutex_t *forks, int nb)
{
	int i;
	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&forks[i], NULL) == 0)
			i++;
		else
			return (1);
	}
	return (0);
}

void init_philo(t_philo *philo, int i, t_global *data)
{
	philo->philo_id = i + 1;
	philo->data = data;
	philo->left_fork = &data->forks[i];
    philo->right_fork = &data->forks[(i + 1) % data->nb_of_philosophers];
	philo->nb_of_meal = 0;
	philo->last_meal = data -> time_stamp;
}

int	main(int ac, char **av)
{
	t_global data;
	t_philo	*philo;
	int i;
	
	i = 0;
	data.time_stamp = get_time_in_ms();
	data.someone_died = 0;
	if (ac == 5 || ac == 6)
	{
		if (parsing_global(&data, av))
			return (1);
		data.forks = malloc(sizeof(pthread_mutex_t)*data.nb_of_philosophers);
		if (!data.forks)
			return (1);
		philo = malloc(sizeof(t_philo) * data.nb_of_philosophers);
		if (!philo)
			return (1);
		init_forks(data.forks, data.nb_of_philosophers);
		if (!data.forks)
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
	}
	else
		printf("The program needs 4 or 5 arguments\n");
	return(0);
}
