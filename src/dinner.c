/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:31:39 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/16 11:21:50 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	*dinner_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->death_time = get_time() + philo->table->t_die;
	if (philo->id % 2 == 0)
	{
		usleep(200);
		if (someone_died(philo))
			return (NULL);
	}
	while (philo->table->satieted_philos != philo->table->n_philo)
	{
		if (someone_died(philo))
			return (NULL);
		if (lets_eat(philo) || lets_sleep(philo) || lets_think(philo))
			return (NULL);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
			dinner_routine, &table->philos[i]))
		{
			printf("Error: thread creation failed\n");
			return ;
		}
	}
	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
		{
			printf("Error: thread join failed\n");
			return ;
		}
	}
}
