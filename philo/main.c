/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:03:13 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:57:04 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

int	main(int argc, char *argv[])
{
	t_arg		*arg;
	t_philo		**philos;

	if (argc != 5 && argc != 6)
	{
		write(2, "error\n", 6);
		return (1);
	}
	arg = arg_init(argc, argv);
	if (!arg)
		return (1);
	pthread_mutex_lock(arg->thread_make_mutex);
	philos = philo_init(arg);
	pthread_mutex_unlock(arg->thread_make_mutex);
	monitoring_thread(philos);
	free_all(arg, philos);
	while (1)
	{
		if (end_flag_check(arg))
			return (0);
		usleep(100);
	}
	return (0);
}
