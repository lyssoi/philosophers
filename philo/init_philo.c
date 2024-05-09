/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:41:51 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/09 12:56:06 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static t_philo	*one_philo_init(t_arg *arg, int i);

t_philo	**philo_init(t_arg *arg)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * arg->num_of_philo);
	memset(philos, 0, sizeof(t_philo *) * arg->num_of_philo);
	if (!philos)
		return (NULL);
	while (i < arg->num_of_philo)
	{
		philos[i] = one_philo_init(arg, i);
		if (!philos[i])
		{
			free_philos(philos, i - 1);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

static t_philo	*one_philo_init(t_arg *arg, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_idx = i + 1;
	philo->left = i;
	philo->right = (i + 1) % arg->num_of_philo;
	philo->last_eat_time = get_time();
	philo->num_eat = 0;
	philo->arg = arg;
	philo->last_eat_time_nutex = make_mutex();
	philo->num_eat_mutex = make_mutex();
	if (!(philo->last_eat_time_nutex) \
	|| (!(philo->num_eat_mutex)) \
	|| pthread_create(&(philo->thread), NULL, \
	(void *)thread_philo, (void *)philo) != 0)
	{
		free_philo(philo);
		return (NULL);
	}
	return (philo);
}
