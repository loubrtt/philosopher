/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:12:32 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/24 23:06:41 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
