/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:04:21 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/20 16:28:50 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_global
{
	long			nb_of_philosophers;
	long			nb_of_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_time_eating;
	pthread_t		**all_thread;
    int             i;
	int				nb_of_death;
	pthread_t		*beginning;
	long			time_stamp;
}		t_global;

typedef struct s_philo
{
	int				philo_id;
	long long int	nb_of_meal;
	long long int	time_last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread_of_philo;
}		t_philo;

long long	ft_atoll(char *str);
long	get_time_in_ms(void);

#endif