/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:44:02 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/09 11:45:46 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	free_philo(t_philo *philo)
{
	if (philo->last_eat_time_nutex)
		mutex_destroy_and_free(philo->last_eat_time_nutex);
	if (philo->num_eat_mutex)
		mutex_destroy_and_free(philo->num_eat_mutex);
	if (philo->thread)
		pthread_join(philo->thread, NULL);
	free(philo);
}

void	free_philos(t_philo **philos, int i)
{
	while (i >= 0)
	{
		free_philo(philos[i]);
		i--;
	}
	free(philos);
}
