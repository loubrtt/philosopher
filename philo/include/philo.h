/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:04:21 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/20 14:54:36 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_global
{
	long			nb_of_philosophers;
	long			nb_of_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_time_eating;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	someone_dead;
	pthread_mutex_t	someone_dead_check;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	is_philo_dead;
	pthread_t		**all_thread;
	int				i;
	int				nb_of_death;
	pthread_t		*beginning;
	int				someone_died;
	pthread_mutex_t	*forks;
	long			time_stamp;
	int				all_philo_eat;
}					t_global;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	long long int	nb_of_meal;
	long long int	last_meal;
	t_global		*data;
	int				time;
}					t_philo;

long long			ft_atoll(char *str);
long				get_time_in_ms(void);
void				init_philo(t_philo *philo, int i, t_global *data);
int					init_forks(pthread_mutex_t *forks, int nb);
int					return_function(int i);
void				*routine(void *arg);
int					is_dead(t_philo *philo);
int					what_time(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				wake_up(t_philo *philo);
void				unlocking(t_philo *philo);
int					locking(t_philo *philo);
int					safe_check_someone_died(t_global *data);
void				destroy_mutexs(t_global *data);
void				free_structs(t_global *data, t_philo *philo, int ac);
int					safe_check_all_philo_eat(t_global *data);
int					safe_check_if_philo_died(t_philo *philo);
int					ft_usleep(int time, t_philo *philo);
int					print_status(t_philo *philo, char *msg);

#endif