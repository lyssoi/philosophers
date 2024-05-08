/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:48:07 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:58:12 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	monitoring_complete(int endphilo, int num, t_arg *arg);
static int	compare_num_eat(t_philo *philo);
static int	monitoring_die(t_philo *philo);

void	monitoring_thread(t_philo **philos)
{
	int		i;
	int		num;
	int		endphilo;
	t_arg	*arg;

	arg = philos[0]->arg;
	num = arg->num_of_philo;
	pthread_mutex_lock(arg->thread_make_mutex);
	pthread_mutex_unlock(arg->thread_make_mutex);
	while (1)
	{
		i = 0;
		endphilo = 0;
		while (i < num)
		{
			endphilo += compare_num_eat(philos[i]);
			if (monitoring_die(philos[i]))
				return ;
			i++;
			usleep(100);
		}
		if (monitoring_complete(endphilo, num, arg))
			return ;
		usleep(100);
	}
}

static int	monitoring_complete(int endphilo, int num, t_arg *arg)
{
	if (arg->num_of_must_eat == -1)
		return (0);
	if (endphilo == num)
	{
		mutex_end_change(arg->end_mutex, &(arg->end_flag));
		return (1);
	}
	return (0);
}

static int	compare_num_eat(t_philo *philo)
{
	int	num_eat;

	if (philo->arg->num_of_must_eat == -1)
		return (0);
	num_eat = num_eat_check(philo);
	if (num_eat >= philo->arg->num_of_must_eat)
		return (1);
	return (0);
}

static int	monitoring_die(t_philo *philo)
{
	long	last_eat_time;

	last_eat_time = last_eat_check(philo);
	if (get_time() - last_eat_time >= philo->arg->time_to_die)
	{
		mutex_end_change(philo->arg->end_mutex, &(philo->arg->end_flag));
		print_philo(philo->arg, philo, "is died");
		return (1);
	}
	return (0);
}
