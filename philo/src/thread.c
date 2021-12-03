/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:07:22 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/03 00:08:05 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	message(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	message(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->lock);
	message(table, philo->id, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&table->lock);
	sleeep(table->time_eat, table);
	(philo->nb_eat)++;
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
}

void	*thread(void *arg)
{
	int		i;
	t_philo	*philo;
	t_table	*table;

	i = 0;
	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		eat(philo);
		if (table->check)
			break ;
		pthread_mutex_lock(&table->lock);
		if (table->someone_died)
			break ;
		pthread_mutex_unlock(&table->lock);
		message(table, philo->id, "is sleeping");
		sleeep(table->time_sleep, table);
		message(table, philo->id, "is thinking");
		i++;
	}
	if (table->someone_died)
		pthread_mutex_unlock(&table->lock);
	return (NULL);
}

void	endd(t_table *table, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->write);
}

void	checker(t_table *table, t_philo *p)
{
	int	i;

	while (!(table->check))
	{
		i = -1;
		while (++i < table->philo_count && !(table->someone_died))
		{
			pthread_mutex_lock(&table->lock);
			if (time_diff(p[i].last_eat, get_time()) > table->time_death)
			{
				message(table, i, "died");
				table->someone_died = 1;
			}
			pthread_mutex_unlock(&table->lock);
			usleep(100);
		}
		if (table->someone_died)
			break ;
		i = 0;
		while (1)
		{
			pthread_mutex_lock(&table->lock);
			if (table->nb_eat != -1 && i < table->philo_count && p[i].nb_eat >= (table->nb_eat - 1))
				i++;
			else
			{
				pthread_mutex_unlock(&table->lock);
				break ;
			}
			pthread_mutex_unlock(&table->lock);
		}
		if (i == table->philo_count)
		{
			pthread_mutex_lock(&table->lock);
			table->check = 1;
			pthread_mutex_unlock(&table->lock);
		}
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
