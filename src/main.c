/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:16:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/03/31 11:31:27 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

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
	if (start_dinner(table))
	{}
}
