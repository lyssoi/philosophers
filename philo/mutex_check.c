/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:23:52 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 15:39:40 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_eat_check(t_philo *philo)
{
	int	num_eat;

	pthread_mutex_lock(philo->num_eat_mutex);
	num_eat = philo->num_eat;
	pthread_mutex_unlock(philo->num_eat_mutex);
	return (num_eat);
}

long	last_eat_check(t_philo *philo)
{
	long	last_eat_time;

	pthread_mutex_lock(philo->last_eat_time_nutex);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(philo->last_eat_time_nutex);
	return (last_eat_time);
}

int	end_flag_check(t_arg *arg)
{
	int	end_flag;

	pthread_mutex_lock(arg->end_mutex);
	end_flag = arg->end_flag;
	pthread_mutex_unlock(arg->end_mutex);
	return (end_flag);
}

int	fork_check(t_arg *arg, int fork)
{
	pthread_mutex_lock(arg->fork_mutex[fork]);
	if (arg->fork[fork] == NOT_IN_USE)
	{
		pthread_mutex_unlock(arg->fork_mutex[fork]);
		return (NOT_IN_USE);
	}
	pthread_mutex_unlock(arg->fork_mutex[fork]);
	return (IN_USE);
}
