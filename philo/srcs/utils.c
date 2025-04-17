/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:12:32 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/13 19:50:07 by lobriott         ###   ########.fr       */
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

long long int	ft_atoll(char *str)
{
	long long int	nbr;
	int				minus;
	int				i;

	nbr = 0;
	minus = 1;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		while (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				minus = -minus;
			i++;
		}
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr * minus);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

int	init_forks(pthread_mutex_t *forks, int nb)
{
	int	i;

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

void	init_philo(t_philo *philo, int i, t_global *data)
{
	philo->philo_id = i + 1;
	philo->data = data;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->nb_of_philosophers];
	philo->nb_of_meal = 0;
	philo->last_meal = data -> time_stamp;
}
