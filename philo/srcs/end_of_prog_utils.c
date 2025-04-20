/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:20:53 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/20 15:12:02 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutexs(t_global *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	pthread_mutex_destroy(&data->someone_dead);
	pthread_mutex_destroy(&data->eating_mutex);
	pthread_mutex_destroy(&data->someone_dead_check);
}

void	free_structs(t_global *data, t_philo *philo, int ac)
{
	if (ac == 5 || ac == 6)
	{
		if (!data->someone_died)
			printf("\n\nFin du programme, aucun mort.\n");
		else
			printf("\n\nFin du programme, un philo est mort.\n");
		destroy_mutexs(data);
		free(data->forks);
		free(philo);
	}
	else
		printf("The program needs 4 or 5 arguments\n");
}
