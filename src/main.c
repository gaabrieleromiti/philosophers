/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:16:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/14 18:57:16 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	clean_up(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
		pthread_mutex_destroy(&table->forks[i].fork);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	if (table)
		free(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	
	table = malloc(sizeof(t_table));
	if (!table)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	if (init(argc, argv, table))
		exit(1);
	start_dinner(table);
	clean_up(table);
	return (0);
}
