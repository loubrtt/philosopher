/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:12:32 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/19 16:12:35 by lobriott         ###   ########.fr       */
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
	while (str[i] > 8 && str[i] < 14 || str[i] == 32)
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
