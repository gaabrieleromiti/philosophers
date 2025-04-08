/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:28:40 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/07 18:33:42 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	init_table(char **argv, t_table *table)
{
	table->n_philo = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->n_meals = ft_atoi(argv[5]);
	else
		table->n_meals = -1;
	table->death = 0;
	table->satieted_philos = 0;

	// Initialize mutexes
	if (pthread_mutex_init(&table->death_lock, NULL) != 0 ||
		pthread_mutex_init(&table->satieted_lock, NULL) != 0 ||
		pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		exit(1);
	}
}

static int	init_forks(int n, t_table *table)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		table->forks[i].id = i;
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			return (1);
		}
	}
	return (0);
}

static void	init_philos(int n, t_table *table)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].l_fork_in_use = 0;
		table->philos[i].r_fork_in_use = 0;
		table->philos[i].death_time = 0;
		table->philos[i].r_fork = &table->forks[i];
		if (i == n - 1)
			table->philos[i].l_fork = &table->forks[0];
		else
			table->philos[i].l_fork = &table->forks[i + 1];
		table->philos[i].table = table;
	}
}

int	init(int argc, char **argv, t_table *table)
{
	if (input_check(argc, argv))
		return (1);
	init_table(argv, table);
	table->forks = malloc(sizeof(t_fork) * table->n_philo);
	if (!table->forks)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	if (init_forks(table->n_philo, table))
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	init_philos(table->n_philo, table);
	return (0);
}
