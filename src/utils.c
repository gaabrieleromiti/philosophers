/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:54:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/03/29 13:58:00 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_atoi(char *s)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*s == 32) || ((9 <= *s) && (*s <= 13)))
	{
		s++;
	}
	if (*s == 45 || *s == 43)
	{
		if (*s == 45)
			sign = -sign;
		s++;
	}
	while ((48 <= *s) && (*s <= 57))
	{
		res = (res * 10) + (*s - 48);
		s++;
	}
	return (res * sign);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error: gettimeofday failed\n");
		return (1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
