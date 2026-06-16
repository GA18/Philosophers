/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:50:03 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/16 18:27:17 by g-alves-         ###   ########.fr       */
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
			if (philo_died(data, id))
			{
				pthread_mutex_lock(&data->action_lock);
				printf("%ld, %i, died\n",
					get_now(&data->time_value) - data->start_time, id);
				data->end_simulation = TRUE;
				pthread_mutex_unlock(&data->action_lock);
				break ;
			}
			id++;
		}
		usleep(500);
	}
}

t_bool	philo_died(t_data *data, int id)
{
	long	time_now;

	time_now = get_now(&data->time_value);
	if ((time_now - data->philos[id].last_eat) > data->time_to_eat)
		return (TRUE);
	return (FALSE);
}
