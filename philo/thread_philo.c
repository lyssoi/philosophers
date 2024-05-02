/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:15:33 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/02 20:00:17 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	update_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(philo->last_eat_time_nutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(philo->last_eat_time_nutex);
}

void	update_num_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->num_eat_mutex);
	philo->num_eat++;
	pthread_mutex_unlock(philo->num_eat_mutex);
}

void	eat_after(t_philo *philo)
{
	fork_chag_not_use(philo, philo->right);
	fork_chag_not_use(philo, philo->left);
	update_last_eat_time(philo);
	update_num_eat(philo);
}

void	thread_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->thread_make_mutex);
	pthread_mutex_unlock(philo->arg->thread_make_mutex);
	if (philo->philo_idx % 2 == 0)
		ft_msleep(philo, philo->arg->time_to_eat);
	while(1)
	{
		if (fork_check(philo->arg, philo->left) == NOT_IN_USE)
		{
			fork_chage_use(philo, philo->left);
			if (!right_fork_check(philo->arg, philo))
				return ;
			fork_chage_use(philo, philo->right);
			print_philo(philo->arg,philo,"is eating", get_time());
			ft_msleep(philo,philo->arg->time_to_eat);
			if (end_flag_check_in_thread(philo, IN_USE, IN_USE))
				return ;
			eat_after(philo);
			print_philo(philo->arg,philo,"is sleeping", get_time());
			ft_msleep(philo,philo->arg->time_to_sleep);
			if (end_flag_check_in_thread(philo, NOT_IN_USE, NOT_IN_USE))
				return ;
			print_philo(philo->arg,philo,"is thinking", get_time());
		}
		usleep(100);
	}
}
