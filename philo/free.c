/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:43:21 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/09 12:54:12 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	free_all(t_arg *arg, t_philo **philos)
{
	free_philos(philos, arg->num_of_philo - 1);
	arg_mutex_free(arg, SUCCESS);
	free(arg->fork);
	free(arg);
}

void	arg_mutex_free(t_arg *arg, int errorno)
{
	if (errorno == SUCCESS)
		fork_mutex_free(arg, arg->num_of_philo - 1);
	if (arg->print_mutex)
		mutex_destroy_and_free(arg->print_mutex);
	if (arg->end_mutex)
		mutex_destroy_and_free(arg->end_mutex);
	if (arg->thread_make_mutex)
		mutex_destroy_and_free(arg->thread_make_mutex);
}

void	mutex_destroy_and_free(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
}

void	fork_mutex_free(t_arg *arg, int i)
{
	while (i >= 0)
	{
		mutex_destroy_and_free(arg->fork_mutex[i]);
		i--;
	}
	free(arg->fork_mutex);
}

void	arg_free(t_arg *arg, int errorno)
{
	arg_mutex_free(arg, errorno);
	free(arg->fork);
	free(arg);
}
