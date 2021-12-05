/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:06:38 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/05 15:35:59 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	sleeep(long long time, t_table *table)
{
	long long	i;

	i = get_time();
	while (1)
	{
		pthread_mutex_lock(&table->lock);
		if (table->someone_died)
			break ;
		pthread_mutex_unlock(&table->lock);
		if (time_diff(i, get_time()) >= time)
			break ;
		usleep(50);
	}
	if (table->someone_died)
		pthread_mutex_unlock(&table->lock);
}

void	message(t_table *table, int id, char *s)
{
	pthread_mutex_lock(&(table->write));
	if (!(table->someone_died))
		printf("%-8lld %-3d %s\n", get_time() - table->start_time, id + 1, s);
	pthread_mutex_unlock(&(table->write));
	return ;
}
