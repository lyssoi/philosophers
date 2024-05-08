/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:43:21 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 13:56:55 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	mutex_destroy_and_free(pthread_mutex_t *mutex);

void	free_all(t_arg *arg, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		mutex_destroy_and_free(philos[i]->last_eat_time_nutex);
		mutex_destroy_and_free(philos[i]->num_eat_mutex);
		mutex_destroy_and_free(arg->fork_mutex[i]);
		free(philos[i]);
		i++;
	}
	free(arg->fork_mutex);
	mutex_destroy_and_free(arg->end_mutex);
	mutex_destroy_and_free(arg->thread_make_mutex);
	mutex_destroy_and_free(arg->print_mutex);
	free(philos);
	free(arg->fork);
	free(arg);
}

static void	mutex_destroy_and_free(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
}
