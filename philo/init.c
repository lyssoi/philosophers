/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:48:45 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/09 12:55:21 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

pthread_mutex_t	*make_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		return (NULL);
	}
	return (mutex);
}

int	arg_fork_init(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_of_philo)
	{
		arg->fork[i] = NOT_IN_USE;
		arg->fork_mutex[i] = make_mutex();
		if (!(arg->fork_mutex[i]))
		{
			fork_mutex_free(arg, i - 1);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	arg_init_mutex(t_arg *arg)
{
	int	errorno;

	arg->fork_mutex = malloc(sizeof(pthread_mutex_t *) * arg->num_of_philo);
	if (!(arg->fork_mutex))
		return (ERROR);
	arg->fork = malloc(sizeof(int) * arg->num_of_philo);
	if (!(arg->fork))
	{
		free(arg);
		return (ERROR);
	}
	arg->print_mutex = make_mutex();
	arg->end_mutex = make_mutex();
	arg->thread_make_mutex = make_mutex();
	errorno = arg_fork_init(arg);
	if (!errorno || !(arg->print_mutex) \
	|| !(arg->end_mutex) || !(arg->thread_make_mutex))
	{
		arg_free(arg, errorno);
		return (ERROR);
	}
	return (SUCCESS);
}

int	argument_error(int argc, char *argv[])
{
	if (ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0
		|| (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (ERROR);
	return (SUCCESS);
}

t_arg	*arg_init(int argc, char *argv[])
{
	t_arg	*arg;
	int		i;

	if (argument_error(argc, argv) == ERROR)
		return (NULL);
	i = 0;
	arg = malloc(sizeof(t_arg));
	memset(arg, 0, sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->num_of_must_eat = -1;
	if (argc == 6)
		arg->num_of_must_eat = ft_atoi(argv[5]);
	arg->end_flag = IS_NOT_END;
	arg->start_time = get_time();
	if (arg_init_mutex(arg) == ERROR)
	{
		free(arg);
		return (NULL);
	}
	return (arg);
}
