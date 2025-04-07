/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:27:27 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/07 15:47:37 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	lets_eat(t_philo *philo)
{
	if (grab_forks(philo))
		return (1);
	philo->last_meal = get_time();
	print_action(philo, "is eating");
	usleep(philo->table->t_eat * 1000);
	release_forks(philo);
	if (philo->table->n_meals != -1)
	{
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->table->n_meals)
		{
			pthread_mutex_lock(&philo->table->satieted_lock);
			philo->table->satieted_philos++;
			pthread_mutex_unlock(&philo->table->satieted_lock);
		}
	}
	return (0);
}

int	lets_sleep(t_philo *philo)
{
	if (someone_died(philo))
		return (1);
	print_action(philo, "is sleeping");
	usleep(philo->table->t_sleep * 1000);
	return (0);
}

int	lets_think(t_philo *philo)
{
	if (someone_died(philo))
		return (1);
	print_action(philo, "is thinking");
	return (0);
}

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
	if (philo->l_fork_in_use)
	{
		pthread_mutex_unlock(&philo->l_fork->fork);
		philo->l_fork_in_use = 0;
	}
	if (philo->r_fork_in_use)
	{
		pthread_mutex_unlock(&philo->r_fork->fork);
		philo->r_fork_in_use = 0;
	}
	return (0);
}

void	print_action(t_philo *p, char *action)
{
	phtread_mutex_lock(p->table->print_lock);
	printf("%zu %d %s\n", get_time(), p->id, action);
	phtread_mutex_unlock(p->table->print_lock);
}

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->death)
	{
		phtread_mutex_unlock(&philo->table->death_lock);
		release_forks(philo);
		return (1);
	}
	if (philo->last_meal + philo->table->t_die < get_time())
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
