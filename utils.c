/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 19:46:03 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 20:35:04 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	type_end_simulation(t_data *data, int id)
{
	if (philo_died(data, id))
	{
		printf("%ld %i died\n", get_now() - data->start_time, id);
		data->end_simulation = TRUE;
		return (DEATH);
	}
	if (is_satisfied(data, id))
		return (SATISFIED);
	return (CONTINUE);
}

t_bool	philo_died(t_data *data, int id)
{
	long	time_now;

	time_now = get_now();
	if ((time_now - data->philos[id].last_eat) > data->time_to_die)
		return (TRUE);
	return (FALSE);
}

t_bool	is_satisfied(t_data *data, int id)
{
	if (data->must_eat)
	{
		if (data->philos[id].count_eat >= data->must_eat
			&& !data->philos[id].satisfied)
		{
			data->philos[id].satisfied = TRUE;
			data->all_satisfied += 1;
			data->end_simulation = TRUE;
		}
		if (data->all_satisfied == data->number_of_philosophers)
			return (TRUE);
	}
	return (FALSE);
}
