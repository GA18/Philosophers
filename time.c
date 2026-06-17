/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:34:59 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 11:09:39 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_now(void)
{
	struct timeval	time_value;
	long			allsec_in_ms;
	long			usec_in_ms;

	gettimeofday(&time_value, NULL);
	allsec_in_ms = time_value.tv_sec * 1000L;
	usec_in_ms = time_value.tv_usec / 1000;
	return (allsec_in_ms + usec_in_ms);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_now();
	while ((get_now() - start) < ms)
		usleep(10);
}
