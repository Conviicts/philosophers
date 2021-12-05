/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:07:22 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/05 15:25:34 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	message(table, philo->id, "has taken a fork");
	message(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->lock);
	message(table, philo->id, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&table->lock);
	sleeep(table->time_eat, table);
	pthread_mutex_lock(&table->lock);
	(philo->nb_eat)++;
	pthread_mutex_unlock(&table->lock);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
}

void	thread2(t_table *table, t_philo *philo)
{
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&table->lock);
		if (table->check)
			break ;
		if (table->someone_died)
			break ;
		pthread_mutex_unlock(&table->lock);
		message(table, philo->id, "is sleeping");
		sleeep(table->time_sleep, table);
		message(table, philo->id, "is thinking");
	}	
}

void	*thread(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		usleep(15000);
	thread2(table, philo);
	if (table->someone_died || table->check)
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
