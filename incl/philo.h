/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:19:19 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/07 15:23:35 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	int		id;
	int		in_use;
	t_mutex	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			meals_eaten;
	int			l_fork_in_use;
	int			r_fork_in_use;
	size_t		death_time;
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	thread;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_meals;
	int		satieted_philos;
	int		death;
	t_mutex	satieted_lock;
	t_mutex	death_lock;
	t_mutex	print_lock;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

// actions.c
int		eat(t_philo *philo);
void	print_action(t_philo *p, char *action);

// dinner.c
void	dinner_routine(void *philosopher);
int		start_dinner(t_table *table);

// init.c
static void	init_table(char **argv, t_table *table);
static int	init_forks(int n, t_table *table);
static void	init_philos(int n, t_table *table);
int			init(int argc, char **argv, t_table *table);

// input.c
static int	print_error(int i);
int			input_check(int argc, char **argv);

// utils.c
int			ft_atoi(char *s);
size_t		get_time(void);

#endif
