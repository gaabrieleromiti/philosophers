/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:48:17 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/16 18:29:02 by gromiti          ###   ########.fr       */
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

static int	print_error(int i)
{
	if (i == 1)
		printf("Error: Wrong number of philosophers\n");
	else if (i == 2)
		printf("Error: Wrong time to die\n");
	else if (i == 3)
		printf("Error: Wrong time to eat\n");
	else if (i == 4)
		printf("Error: Wrong time to sleep\n");
	else if (i == 5)
		printf("Error: Wrong number of times to eat\n");
	return (1);
}

int	input_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	while (argv[++i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (print_error(i));
			j++;
		}
		j = 0;
		if (ft_atoi(argv[i]) < 0 || (i == 1 && ft_atoi(argv[i]) == 0))
			return (print_error(i));
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	size_tot;

	size_tot = nmemb * size;
	if (nmemb + size < size || size + nmemb < nmemb || size_tot > 2147483424)
		return (NULL);
	res = malloc(size_tot);
	if (res == NULL)
		return (NULL);
	while (size_tot--)
		((char *)res)[size_tot] = 0;
	return (res);
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
