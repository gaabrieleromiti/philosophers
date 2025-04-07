/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:31:39 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/07 15:47:44 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	mutex_check(t_mutex *mutex, int alive)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Error: mutex lock failed\n");
		return (1);
	}
	if (!alive)
	{
		if (pthread_mutex_unlock(mutex) != 0)
		{
			printf("Error: mutex unlock failed\n");
			return (1);
		}
		return (0);
	}
	return (1);
}

void	dinner_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->death_time = get_time() + philo->table->t_die;
	if (philo->id % 2 == 0)
		
}

int	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, dinner_routine, &table->philos[i]))
		{
			printf("Error: thread creation failed\n");
			return (1);
		}
	}
	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
		{
			printf("Error: thread join failed\n");
			return (1);
		}
	}
}