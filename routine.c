/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:30:04 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 21:06:51 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id & 1)
		ft_usleep(1);
	while (1)
	{
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
	lock_action(philo, (RIGHT_HAND | LEFT_HAND | ACTION), LOCK);
	pthread_mutex_lock(&philo->data->action_lock);
	//pthread_mutex_lock(&philo->data->forks[]);
	pthread_mutex_lock(&philo->data->action_lock);
	if (philo->data->end_simulation == FALSE)
	{
		philo->last_eat = get_now();
		printf("%ld %i has taken a fork\n",
			philo->last_eat - philo->data->start_time, philo->id);
		printf("%ld %i is eating\n",
			philo->last_eat - philo->data->start_time, philo->id);
		ft_usleep(philo->data->time_to_eat);
		lock_action(philo, (RIGHT_HAND | LEFT_HAND | ACTION), UNLOCK);
	}
	else
		lock_action(philo, (RIGHT_HAND | LEFT_HAND | ACTION), UNLOCK);
	lock_action(philo, ACTION, LOCK);
	philo->count_eat += 1;
	lock_action(philo, ACTION, UNLOCK);
	return (0);
}

int	sleeping(t_philo *philo)
{
	lock_action(philo, ACTION, LOCK);
	if (philo->data->end_simulation == FALSE)
	{
		printf("%ld %i is sleeping\n",
			get_now() - philo->data->start_time, philo->id);
	}
	else
	{
		lock_action(philo, ACTION, UNLOCK);
		return (1);
	}
	lock_action(philo, ACTION, UNLOCK);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	lock_action(philo, ACTION, LOCK);
	if (philo->data->end_simulation == FALSE)
	{
		printf("%ld %i is thinking\n",
			get_now() - philo->data->start_time, philo->id);
	}
	else
	{
		lock_action(philo, ACTION, UNLOCK);
		return (1);
	}
	ft_usleep(5);
	lock_action(philo, ACTION, UNLOCK);
	return (0);
}

void	lock_action(t_philo *philo, unsigned int flags, unsigned int type)
{
	pthread_mutex_t	*mtx[3];
	unsigned int	index;

	mtx[0] = &philo->data->forks[philo->left_hand];
	mtx[1] = &philo->data->forks[philo->right_hand];
	mtx[2] = &philo->data->action_lock;

	index = 0;
	while (index < 3)
	{
		if (flags & (1 << index) && type == LOCK)
			pthread_mutex_lock(mtx[index]);
		else if (flags & (1 << index) && type == UNLOCK)
			pthread_mutex_unlock(mtx[index]);
		index++;
	}
}
