/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:50:03 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 11:09:47 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
		return (1);
	data = parser_philo(data, argc, argv);
	printf("Iniciando Threads\n");
	start_simulation(data);
	cleanup(data);
	return (0);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
	check_simulation(data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	check_simulation(t_data *data)
{
	int	id;

	id = 0;
	while (!data->end_simulation)
	{
		id = 0;
		while (id < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->action_lock);
			if (philo_died(data, id))
			{
				printf("%ld %i died\n",
					get_now() - data->start_time, id);
				data->end_simulation = TRUE;
				pthread_mutex_unlock(&data->action_lock);
				break ;
			}
			if (is_satisfied(data, id))
				break ;
			id++;
			pthread_mutex_unlock(&data->action_lock);
		}
		ft_usleep(10);
	}
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
		}
		if (data->all_satisfied == data->number_of_philosophers)
			return (TRUE);
	}
	return (FALSE);
}
