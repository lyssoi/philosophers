/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:03:13 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/09 12:56:32 by soljeong         ###   ########.fr       */
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
		return (print_error());
	arg = arg_init(argc, argv);
	if (!arg)
		return (print_error());
	pthread_mutex_lock(arg->thread_make_mutex);
	philos = philo_init(arg);
	if (!philos)
	{
		arg_free(arg, SUCCESS);
		return (print_error());
	}
	pthread_mutex_unlock(arg->thread_make_mutex);
	monitoring_thread(philos);
	while (1)
	{
		if (end_flag_check(arg))
			break ;
		usleep(100);
	}
	free_all(arg, philos);
	return (0);
}
