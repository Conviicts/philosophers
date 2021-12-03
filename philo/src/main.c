/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:10:22 by jode-vri          #+#    #+#             */
/*   Updated: 2021/12/03 00:10:34 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		ret;

	if (ac < 5 || ac > 6)
		return (error("Error\n"));
	ret = init(&table, av);
	if (!ret)
		return (error2(ret));
	table.start_time = get_time();
	if (table.philo_count == 1)
	{
		message(&table, 0, "has taken a fork");
		usleep(table.time_death * 1000);
		message(&table, 0, "died");
		return (0);
	}
	if (!start(&table))
		return (error("Error2\n"));
	return (0);
}
