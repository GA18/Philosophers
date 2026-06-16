/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 18:02:42 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/16 18:34:23 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*parser_philo(t_data *data, int argc, char **argv)
{
	data = init_philo(data, ft_atoi((const char *)argv[1]));
	if (!data)
		return (NULL);
	data->number_of_philosophers = ft_atoi((const char *)argv[1]);
	data->time_to_die = ft_atoi((const char *)argv[2]);
	data->time_to_eat = ft_atoi((const char *)argv[3]);
	data->time_to_sleep = ft_atoi((const char *)argv[4]);
	if (argc == 6)
		data->must_eat
			= ft_atoi((const char *)argv[5]);
	data->start_time = get_now(&data->time_value);
	data->end_simulation = FALSE;
	return (data);
}

t_data	*init_philo(t_data *data, unsigned long size)
{
	int	index_id;

	data = malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
	data->philos = malloc(sizeof(t_philo) * size);
	memset(data->philos, 0, sizeof(t_philo) * size);
	data->forks = malloc (sizeof(pthread_mutex_t) * size);
	if (!data || !data->philos || !data->forks)
		return (0);
	index_id = 0;
	while (index_id < size)
	{
		data->philos[index_id].id = index_id;
		data->philos[index_id].count_eat = 0;
		data->philos[index_id].last_eat = get_now(&data->time_value);
		data->philos[index_id].left_hand = index_id;
		data->philos[index_id].right_hand
			= (size + (index_id - 1)) % size;
		data->philos[index_id].data = data;
		pthread_mutex_init(&data->forks[index_id], NULL);
		index_id++;
	}
	pthread_mutex_init(&data->action_lock, NULL);
	return (data);
}

unsigned long	ft_atoi(const char *nptr)
{
	size_t				index_string;
	unsigned long		sign;
	unsigned long		number;

	index_string = 0;
	while ((nptr[index_string] == ' ')
		|| ((nptr[index_string] >= 9)
			&& (nptr[index_string] <= 13)))
		index_string++;
	sign = 1;
	if ((nptr[index_string] == '-') || (nptr[index_string] == '+'))
	{
		if (nptr[index_string] == '-')
			sign = -1;
		index_string++;
	}
	number = 0;
	while ((nptr[index_string] >= '0') && (nptr[index_string] <= '9'))
	{
		number = (number * 10) + (nptr[index_string] - '0');
		index_string++;
	}
	return (sign * number);
}
