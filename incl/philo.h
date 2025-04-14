/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:19:19 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/14 20:35:56 by gromiti          ###   ########.fr       */
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
typedef struct s_table t_table;

typedef struct s_fork
{
	int		id;
	t_mutex	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	int*		l_fork_in_use;
	int*		r_fork_in_use;
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
	size_t	start;
	int		death;
	t_mutex	satieted_lock;
	t_mutex	death_lock;
	t_mutex	print_lock;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

// actions_utils.c
int		grab_forks(t_philo *philo);
int		release_forks(t_philo *philo);
int		someone_died(t_philo *philo);
void	print_action(t_philo *philo, char *action);
size_t	get_time(void);

// actions.c
int		lets_eat(t_philo *philo);
int		lets_sleep(t_philo *philo);
int		lets_think(t_philo *philo);

// dinner.c
void	*dinner_routine(void *philosopher);
void	start_dinner(t_table *table);

// init_utils.c
int			ft_atoi(char *s);
int			input_check(int argc, char **argv);
void		*ft_calloc(size_t nmemb, size_t size);


// init.c
int	init(int argc, char **argv, t_table *table);

#endif
