/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:15:33 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:57:40 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	thread_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->thread_make_mutex);
	pthread_mutex_unlock(philo->arg->thread_make_mutex);
	if (philo->philo_idx % 2 == 0)
		ft_msleep(philo, philo->arg->time_to_eat);
	while (1)
	{
		if (fork_check(philo->arg, philo->left) == NOT_IN_USE)
		{
			fork_chage_use(philo, philo->left);
			if (!right_fork_check(philo->arg, philo))
				return ;
			fork_chage_use(philo, philo->right);
			eating(philo);
			if (end_flag_check_in_thread(philo, IN_USE, IN_USE))
				return ;
			print_philo(philo->arg, philo, "is sleeping");
			ft_msleep(philo, philo->arg->time_to_sleep);
			if (end_flag_check_in_thread(philo, NOT_IN_USE, NOT_IN_USE))
				return ;
			print_philo(philo->arg, philo, "is thinking");
		}
		usleep(100);
	}
}
