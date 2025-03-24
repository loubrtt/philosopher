/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:04:21 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/24 17:28:18 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

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
	int				someone_died;
	pthread_mutex_t	*forks;
	long			time_stamp;
}		t_global;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	pthread_t				thread_id;
	long long int	nb_of_meal;
	long long int	last_meal;
	t_global		*data;
}		t_philo;

long long	ft_atoll(char *str);
long	get_time_in_ms(void);

#endif