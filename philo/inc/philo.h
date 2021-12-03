/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:09:29 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/03 02:31:04 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct	s_table;

typedef struct s_philo
{
	int					id;
	int					died;
	int					nb_eat;
	int					left_fork;
	int					right_fork;
	long long			last_eat;
	struct s_table		*table;
	pthread_t			thread_id;
}						t_philo;

typedef struct s_table
{
	int					philo_count;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					someone_died;
	int					check;
	int					state;
	long long			start_time;
	pthread_mutex_t		lock;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		write;
	t_philo				philos[250];
}						t_table;

int			ft_atoi(const char *str);
void		message(t_table *table, int id, char *s);
long long	get_time(void);
long long	time_diff(long long past, long long pres);
void		sleeep(long long time, t_table *table);

int			start(t_table *table);
void		endd(t_table *table, t_philo *philos);
int			error(char *str);
int			init(t_table *table, char **av);
void		*thread(void *arg);

#endif
