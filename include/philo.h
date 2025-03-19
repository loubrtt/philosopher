/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:04:21 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/19 16:41:26 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_struct
{
	long long int	number_of_philosophers;
	long long int	number_of_forks;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	number_of_time_eating;
    int             i;
}		t_struct;

long long int	ft_atoll(char *str);

#endif