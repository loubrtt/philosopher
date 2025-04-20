/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:49:25 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/20 15:12:21 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i != n - 1)
		i++;
	if (!*s1 && !s2)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	print_status(t_philo *philo, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (safe_check_someone_died(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	timestamp = what_time(philo);
	printf("%lld %d %s\n", timestamp, philo->philo_id, msg);
	if (ft_strncmp(msg, "died", 4) == 0)
	{
		pthread_mutex_lock(&philo->data->someone_dead);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->someone_dead);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}
