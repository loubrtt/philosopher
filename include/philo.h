/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:04:21 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/20 10:17:22 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_global
{
	long long int	nb_of_philosophers;
	long long int	nb_of_forks;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	nb_of_time_eating;
	long long int	**all_philosophers;
    int             i;
	int				nb_of_death;
	long long int	beginning_stamp;
}		t_global;

typedef struct s_philo
{
	int				philo_id;
	long long int	nb_of_meal;
	long long int	time_last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread_of_philo;
}

long long int	ft_atoll(char *str);

#endif