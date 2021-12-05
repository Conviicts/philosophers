/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:10:22 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/05 17:29:57 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker2(t_table *table, t_philo *p, int i)
{
	while (++i < table->philo_count && !(table->someone_died))
	{
		pthread_mutex_lock(&table->lock);
		if (time_cmp(p[i].last_eat, get_time()) > table->time_death)
		{
			message(table, i, "died");
			pthread_mutex_lock(&(table->write));
			table->someone_died = 1;
			pthread_mutex_unlock(&(table->write));
		}
		pthread_mutex_unlock(&table->lock);
		usleep(100);
	}
}

void	checker3(t_table *table, int i)
{
	if (i == table->philo_count)
	{
		pthread_mutex_lock(&table->lock);
		table->check = 1;
		pthread_mutex_unlock(&table->lock);
	}
}

void	checker(t_table *t, t_philo *p)
{
	int	i;

	while (!(t->check))
	{
		i = -1;
		checker2(t, p, i);
		if (t->someone_died)
			break ;
		i = 0;
		while (1)
		{
			pthread_mutex_lock(&t->lock);
			if (t->nb_eat != -1 && i < t->philo_count
				&& p[i].nb_eat >= (t->nb_eat - 1))
				i++;
			else
			{
				pthread_mutex_unlock(&t->lock);
				break ;
			}
			pthread_mutex_unlock(&t->lock);
		}
		checker3(t, i);
	}
}

int	start(t_table *table)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = table->philos;
	while (i < table->philo_count)
	{
		if (pthread_create(&ph[i].thread_id, NULL, thread, &ph[i]))
			return (0);
		pthread_mutex_lock(&table->lock);
		ph[i].last_eat = get_time();
		pthread_mutex_unlock(&table->lock);
		i++;
	}
	checker(table, table->philos);
	endd(table, ph);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		ret;

	if (ac < 5 || ac > 6)
		return (error("Error"));
	ret = init(&table, av);
	if (!ret)
		return (error("Error"));
	table.start_time = get_time();
	if (table.philo_count == 1)
	{
		message(&table, 0, "has taken a fork");
		usleep(table.time_death * 1000);
		message(&table, 0, "died");
		return (0);
	}
	if (!start(&table))
		return (error("Error"));
	return (0);
}
