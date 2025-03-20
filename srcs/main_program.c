/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:03:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/20 16:34:48 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parsing_global(t_global *data, char **av)
{
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
	data->nb_of_time_eating = ft_atoll(av[4]);
	if (data->nb_of_time_eating <= 0)
	{
		printf("Error: Please provide at least one \
			time for eating as input.\n");
		data->i = 1;
	}
	if (data->i)
		return (-1);
	return (0);
}

void *eating (t_global *data)
{
	if (!usleep(data->time_to_eat))
	{
		printf("mange");
		return (NULL);
	}
	printf("Erreur, le philosophe n'a pas mangé\n");
	return (NULL);
}

void	*sleeping(t_global *data)
{
	if (!usleep(data->time_to_sleep))
	{
		printf("dors");
		return (NULL);
	}
	printf("Erreur, le philosophe n'a pas dormi\n");
	return (NULL);
}

int	init_thread(t_global *data, t_philo *philo, int num_of_philo)
{
	pthread_create(data->all_thread[num_of_philo], NULL, eating, data);
	pthread_join(data->all_thread[num_of_philo], NULL);
	pthread_create(data->all_thread[num_of_philo], NULL, sleeping, data);
	pthread_join(data->all_thread[num_of_philo], NULL);
}

int	main(int ac, char **av)
{
	t_global data;
	t_philo	philo;
	long time;
	
	data.time_stamp = get_time_in_ms();
	if (ac == 4 || ac == 5)
	{
		parsing_global(&data, av);
		init_threads(&data, &philo);
	}
	else
		printf("The program needs 4 or 5 arguments\n");
}
