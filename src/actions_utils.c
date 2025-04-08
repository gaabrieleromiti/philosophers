/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:20:52 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/08 11:54:12 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	grab_forks(t_philo *philo)
{
	if (someone_died(philo))
		return (1);
	if (pthread_mutex_lock(&philo->l_fork->fork))
	{
		printf("Error: mutex lock failed\n");
		return (1);
	}
	print_action(philo, "has taken a fork");
	philo->l_fork_in_use = 1;
	if (someone_died(philo))
		return (1);
	if (pthread_mutex_lock(&philo->r_fork->fork))
	{
		pthread_mutex_unlock(&philo->l_fork->fork);
		philo->l_fork_in_use = 0;
		printf("Error: mutex lock failed\n");
		return (1);
	}
	print_action(philo, "has taken a fork");
	philo->r_fork_in_use = 1;
	if (someone_died(philo))
		return (1);
	return (0);
}

int	release_forks(t_philo *philo)
{
	if (philo->r_fork_in_use)
	{
		pthread_mutex_unlock(&philo->r_fork->fork);
		philo->r_fork_in_use = 0;
	}
	if (philo->l_fork_in_use)
	{
		pthread_mutex_unlock(&philo->l_fork->fork);
		philo->l_fork_in_use = 0;
	}
	return (0);
}

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->death)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		release_forks(philo);
		return (1);
	}
	if (philo->death_time < get_time())
	{
		print_action(philo, "died");
		philo->table->death = 1;
		pthread_mutex_unlock(&philo->table->death_lock);
		release_forks(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	return (0);
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%zu %d %s\n", get_time(), philo->id, action);
	pthread_mutex_unlock(&philo->table->print_lock);
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
