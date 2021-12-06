/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:06:20 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/06 02:54:01 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (0);
	}
	if (pthread_mutex_init(&(table->write), NULL))
		return (0);
	if (pthread_mutex_init(&(table->lock), NULL))
		return (0);
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i;
		table->philos[i].died = 0;
		table->philos[i].nb_eat = 0;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->philo_count;
		table->philos[i].last_eat = 0;
		table->philos[i].table = table;
	}
	return (1);
}

int	init(t_table *table, char **av)
{
	table->philo_count = ft_atoi(av[1]);
	table->time_death = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	table->check = 0;
	table->someone_died = 0;
	if (table->philo_count < 1 || table->time_death < 0 || table->time_eat < 0
		|| table->time_sleep < 0 || table->philo_count > 200)
		return (0);
	if (av[5])
	{
		table->nb_eat = ft_atoi(av[5]);
		if (table->nb_eat <= 0)
			return (0);
	}
	else
		table->nb_eat = -1;
	if (!init_mutex(table) || !init_philos(table))
		return (0);
	return (1);
}
