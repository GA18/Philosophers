/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:30:04 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 16:52:28 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id & 1)
		ft_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->data->action_lock);
		if (philo->data->end_simulation == TRUE)
		{
			pthread_mutex_unlock(&philo->data->action_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->action_lock);
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->action_lock);
	if (philo->data->end_simulation == FALSE)
	{
		pthread_mutex_unlock(&philo->data->action_lock);
		pthread_mutex_lock(&philo->data->forks[philo->left_hand]);
		pthread_mutex_lock(&philo->data->forks[philo->right_hand]);
		pthread_mutex_lock(&philo->data->action_lock);
		philo->last_eat = get_now();
		printf("%ld %i is eating\n",
			philo->last_eat - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->action_lock);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->right_hand]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_hand]);
		pthread_mutex_lock(&philo->data->action_lock);
		philo->count_eat += 1;
		pthread_mutex_unlock(&philo->data->action_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->action_lock);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (philo->data->end_simulation == FALSE)
	{
		pthread_mutex_lock(&philo->data->action_lock);
		printf("%ld %i is sleeping\n",
			get_now() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->action_lock);
		ft_usleep(philo->data->time_to_sleep);
		return (0);
	}
	return (1);
}

int	thinking(t_philo *philo)
{
	if (philo->data->end_simulation == FALSE)
	{
		pthread_mutex_lock(&philo->data->action_lock);
		printf("%ld %i is thinking\n",
			get_now() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->action_lock);
		return (0);
	}
	return (1);
}
