/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:34:59 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/16 15:22:25 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_now(struct timeval *time_value)
{
	long	allsec_in_ms;
	long	usec_in_ms;

	gettimeofday(time_value, NULL);
	allsec_in_ms = (*time_value).tv_sec * 1000L;
	usec_in_ms = (*time_value).tv_usec / 1000;
	return (allsec_in_ms + usec_in_ms);
}

void	ft_usleep(struct timeval *time_value, long ms)
{
	long	start;

	start = get_now(time_value);
	while ((get_now(time_value) - start) < ms)
		usleep(50);
}
