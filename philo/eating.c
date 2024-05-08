/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:48 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:57:51 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_last_eat_time(t_philo *philo);
static void	update_num_eat(t_philo *philo);

void	eating(t_philo *philo)
{
	print_philo(philo->arg, philo, "is eating");
	update_last_eat_time(philo);
	update_num_eat(philo);
	ft_msleep(philo, philo->arg->time_to_eat);
	fork_chag_not_use(philo, philo->right);
	fork_chag_not_use(philo, philo->left);
}

static void	update_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(philo->last_eat_time_nutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(philo->last_eat_time_nutex);
}

static void	update_num_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->num_eat_mutex);
	philo->num_eat++;
	pthread_mutex_unlock(philo->num_eat_mutex);
}
