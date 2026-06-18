/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:50:03 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 20:38:05 by g-alves-         ###   ########.fr       */
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

	while (!data->end_simulation)
	{
		id = 0;
		while (id < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->action_lock);
			if (type_end_simulation(data, id) & (DEATH | SATISFIED))
			{
				pthread_mutex_unlock(&data->action_lock);
				break ;
			}
			pthread_mutex_unlock(&data->action_lock);
			id++;
		}
		ft_usleep(1);
	}
}
