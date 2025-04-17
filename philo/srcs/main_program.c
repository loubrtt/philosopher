/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:03:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/16 21:40:12 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	data->all_philo_eat = 1;
	if (data->i)
		return (1);
	return (0);
}

int	is_dead(t_philo *philo)
{
	if (safe_check_if_philo_died(philo))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d died\n", what_time(philo),
			philo->philo_id);
		pthread_mutex_lock(&philo->data->someone_dead_check);
		philo->data->someone_died++;
		pthread_mutex_unlock(&philo->data->someone_dead_check);
		usleep(1000);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

int	parsing(t_global *data, t_philo **philo, char **av)
{
	if (parsing_global(data, av))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	if (!data->forks)
		return (1);
	if (init_forks(data->forks, data->nb_of_philosophers))
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

void	init_mutexs(t_global *data)
{
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->finished_mutex, NULL);
	pthread_mutex_init(&data->someone_dead, NULL);
	pthread_mutex_init(&data->eating_mutex, NULL);
	pthread_mutex_init(&data->someone_dead_check, NULL);
	pthread_mutex_init(&data->is_philo_dead, NULL);
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
		init_mutexs(&data);
		while (i < data.nb_of_philosophers)
		{
			init_philo(&philo[i], i, &data);
			pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i]));
			i++;
		}
		i = 0;
		usleep(10);
		while (i < data.nb_of_philosophers)
			pthread_join(philo[i++].thread_id, NULL);
		free_structs(&data, philo, ac);
	}
	return (0);
}
