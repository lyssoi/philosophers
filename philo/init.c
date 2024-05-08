/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:48:45 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:18:48 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

pthread_mutex_t	*make_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

void	arg_fork_init(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_of_philo)
	{
		arg->fork[i] = NOT_IN_USE;
		arg->fork_mutex[i] = make_mutex();
		i++;
	}
}

t_arg	*arg_init(int argc, char *argv[])
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
		arg->num_of_must_eat = ft_atoi(argv[5]);
	arg->fork_mutex = malloc(sizeof(pthread_mutex_t *) * arg->num_of_philo);
	arg->fork = malloc(sizeof(int) * arg->num_of_philo);
	arg_fork_init(arg);
	arg->print_mutex = make_mutex();
	arg->end_mutex = make_mutex();
	arg->thread_make_mutex = make_mutex();
	return (arg);
}

t_philo	**philo_init(t_arg *arg)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * arg->num_of_philo);
	if (!philos)
		return (NULL);
	while (i < arg->num_of_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		philos[i]->philo_idx = i + 1;
		philos[i]->left = i;
		philos[i]->right = (i + 1) % arg->num_of_philo;
		philos[i]->last_eat_time = get_time();
		philos[i]->num_eat = 0;
		philos[i]->arg = arg;
		philos[i]->last_eat_time_nutex = make_mutex();
		philos[i]->num_eat_mutex = make_mutex();
		if (pthread_create(&(philos[i]->thread), NULL, \
		(void *)thread_philo, (void *)philos[i]) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}
