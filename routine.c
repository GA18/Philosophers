/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:30:04 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/16 18:38:25 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (philo->data->end_simulation == FALSE)
	{
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_hand]);
	pthread_mutex_lock(&philo->data->forks[philo->right_hand]);
	philo->last_eat = get_now(&philo->data->time_value);
	pthread_mutex_lock(&philo->data->action_lock);
	printf("%ld %i is eating\n",
		philo->last_eat - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->action_lock);
	ft_usleep(&philo->data->time_value, philo->data->time_to_eat);
	philo->count_eat += 1;
	pthread_mutex_unlock(&philo->data->forks[philo->right_hand]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_hand]);
	return (0);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->action_lock);
	printf("Philosopho [%i] in timestemp [%ld] is sleeping",
		philo->id, get_now(&philo->data->time_value));
	pthread_mutex_unlock(&philo->data->action_lock);
	ft_usleep(&philo->data->time_value, philo->data->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->action_lock);
	printf("Philosopher [%i] in timestemp [%ld] is thinking",
		philo->id, get_now(&philo->data->time_value));
	pthread_mutex_unlock(&philo->data->action_lock);
	return (0);
}
