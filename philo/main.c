/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:03:13 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/02 20:28:42 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t *make_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

void	arg_fork_init(t_arg *arg)
{
	int i;

	i = 0;
	while (i < arg->num_of_philo)
	{
		arg->fork[i] = NOT_IN_USE;
		arg->fork_mutex[i] = make_mutex();
		i++;
	}
}

t_arg *arg_init(int argc, char *argv[])
{
	t_arg	*arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->num_of_must_eat = -1;
	arg->end_flag = IS_NOT_END;
	arg->start_time = get_time();
	if (argc == 6)
		arg->num_of_must_eat =  ft_atoi(argv[5]);
	arg->fork_mutex = malloc(sizeof(pthread_mutex_t *) * arg->num_of_philo);
	arg->fork = malloc(sizeof(int) * arg->num_of_philo);
	arg_fork_init(arg);
	arg->print_mutex = make_mutex();
	arg->end_mutex = make_mutex();
	return (arg);
}


void	monitoring_thread(t_philo **philos)
{
	int	i;
	int	num;
	int	endphilo;
	long last_eat_time;
	int	num_eat;

	i = 0;
	num = philos[0]->arg->num_of_philo;
	endphilo = 0;
	pthread_mutex_lock(philos[0]->arg->thread_make_mutex);
	pthread_mutex_unlock(philos[0]->arg->thread_make_mutex);
	while (1)
	{
		num_eat = num_eat_check(philos[i]);
		if (num_eat == philos[i]->arg->num_of_must_eat)
			endphilo++;
		last_eat_time = last_eat_check(philos[i]);
		if (get_time() - last_eat_time >= philos[i]->arg->time_to_die)
		{
			print_philo(philos[i]->arg, philos[i], "is died", get_time());
			mutex_end_change(philos[i]->arg->end_mutex, &(philos[i]->arg->end_flag));
			return ;
		}
		i++;
		if (i >= num)
		{
			i = 0;
			if (endphilo == num)
			{
				mutex_end_change(philos[i]->arg->end_mutex, &(philos[i]->arg->end_flag));
				return ;
			}
			endphilo = 0;
		}
		usleep(100);
	}
}

t_philo	**philo_init(t_arg *arg)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * arg->num_of_philo);
	
	while (i < arg->num_of_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->philo_idx = i + 1;
		philos[i]->left = i;
		philos[i]->right = (i + 1) % arg->num_of_philo;
		philos[i]->last_eat_time = get_time();
		philos[i]->num_eat = 0;
		philos[i]->arg = arg;
		philos[i]->thread = malloc(sizeof(pthread_t));
		philos[i]->last_eat_time_nutex = make_mutex();
		philos[i]->num_eat_mutex = make_mutex();
		pthread_create(&(philos[i]->thread),NULL,(void *)thread_philo,(void *)philos[i]);
		i++;
	}
	return (philos);
}

int main (int argc, char *argv[])
{
	int			idx;
	t_arg		*arg;
	t_philo		**philos;

	if (argc != 5 && argc != 6)
	{
		write(2,"error\n",6);
		return (1);
	}
	arg = arg_init(argc, argv);
	idx = 0;
	if (!arg)
		return (1);
	int i = 0;
	arg->thread_make_mutex = make_mutex();
	pthread_mutex_lock(arg->thread_make_mutex);
	philos = philo_init(arg);
	pthread_mutex_unlock(arg->thread_make_mutex);
	monitoring_thread(philos);
	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	while (1)
	{
		if (end_flag_check(arg))
			return (0);
		usleep(100);
	}
	return (0);
}
