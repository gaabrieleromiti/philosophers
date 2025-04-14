/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:27:27 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/14 23:05:15 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	lets_eat(t_philo *philo)
{
	if (grab_forks(philo))
		return (1);
	philo->death_time = get_time() + philo->table->t_die;
	print_action(philo, "is eating");
	usleep(philo->table->t_eat * 1000);
	release_forks(philo);
	print_action(philo, "released forks");
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
	size_t	start;

	start = get_time();
	print_action(philo, "is sleeping");
	while (get_time() < start + philo->table->t_sleep)
	{
		if (someone_died(philo))
			return (1);
		usleep(50);
	}
	return (0);
}

int	lets_think(t_philo *philo)
{
	if (someone_died(philo))
		return (1);
	print_action(philo, "is thinking");
	return (0);
}
