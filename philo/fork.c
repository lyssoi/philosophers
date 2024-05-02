/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:00:21 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/02 20:01:36 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	right_fork_check(t_arg *arg, t_philo *philo)
{
	while (1)
	{
		if (end_flag_check_in_thread(philo, IN_USE, NOT_IN_USE))
			return (0);
		if (philo->arg->num_of_philo != 1 && fork_check(arg, philo->right) == NOT_IN_USE)
			break;
		usleep(100);
	}
	return (1);
}

void	fork_chage_use(t_philo *philo, int idx)
{
	pthread_mutex_lock(philo->arg->fork_mutex[idx]);
	philo->arg->fork[idx] = IN_USE;
	print_philo(philo->arg,philo,"has taken a fork", get_time());
}

void	fork_chag_not_use(t_philo *philo, int idx)
{
	philo->arg->fork[idx] = NOT_IN_USE;
	pthread_mutex_unlock(philo->arg->fork_mutex[idx]);
}