/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:03:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/19 16:44:13 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parsing(t_struct *data, char **av)
{
	data->number_of_philosophers = ft_atoll(av[1]);
	if (data->number_of_philosophers < 1)
	{
		printf("Error: Please provide at least
		one philosopher as input.\n");
		data->i = 1;
	}
	data->number_of_forks = data->number_of_philosophers;
	data->time_to_die = ft_atoll(av[2]);
	if (data->time_to_die <= 0)
	{
		printf("Error: Please provide at least one 
			millisecond before dying as input.\n");
		data->i = 1;
	}
	data->time_to_eat = ft_atoll(av[3]);
	if (data->time_to_eat <= 0)
	{
		printf("Error: Please provide at least one 
			millisecond for eating as input.\n");
		data->i = 1;
	}
	data->number_of_time_eating = ft_atoll(av[4]);
	if (data->number_of_time_eating <= 0)
	{
		printf("Error: Please provide at least one 
			time for eating as input.\n");
		data->i = 1;
	}
}

int	main(int ac, char **av)
{
	t_struct data;
	if (ac == 4 || ac == 5)
		parsing(&data, av);
	else
		printf("The program needs 4 or 5 arguments\n");
}