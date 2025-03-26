/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:03:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/26 13:42:44 by lobriott         ###   ########.fr       */
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
