/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g-alves- <g-alves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:46:40 by g-alves-          #+#    #+#             */
/*   Updated: 2026/06/17 08:48:16 by g-alves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_philo
{
	int				id;
	int				left_hand;
	int				right_hand;
	int				count_eat;
	long			last_eat;
	t_bool			satisfied;

	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;

	t_philo			*philos;

	t_bool			end_simulation;
	t_bool			all_satisfied;
	long			start_time;
	struct timeval	time_value;

	pthread_mutex_t	action_lock;
	pthread_mutex_t	*forks;
}	t_data;

t_data			*parser_philo(t_data *data, int argc, char **argv);
t_data			*init_philo(t_data *data, unsigned long size);
unsigned long	ft_atoi(const char *nptr);
void			start_simulation(t_data *data);
void			cleanup(t_data *data);
long			get_now(struct timeval *time_value);
void			ft_usleep(struct timeval *time_value, long ms);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
void			check_simulation(t_data *data);
int				thinking(t_philo *philo);
t_bool			philo_died(t_data *data, int id);
void			*routine(void *ptr);
t_bool			is_satisfied(t_data *data, int id);


#endif