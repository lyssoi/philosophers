/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_flag_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:43:44 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:59:45 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_flag_check_in_thread(t_philo *philo, int left_use, int right_use)
{
	t_arg	*arg;

	arg = philo->arg;
	if (get_time() - philo->last_eat_time >= philo->arg->time_to_die)
		mutex_end_change(philo->arg->end_mutex, &(philo->arg->end_flag));
	if (end_flag_check(arg) == IS_END)
	{
		if (left_use == IN_USE)
		{
			philo->arg->fork[philo->left] = NOT_IN_USE;
			pthread_mutex_unlock(philo->arg->fork_mutex[philo->left]);
		}
		if (right_use == IN_USE)
		{
			philo->arg->fork[philo->right] = NOT_IN_USE;
			pthread_mutex_unlock(philo->arg->fork_mutex[philo->right]);
		}
		return (1);
	}
	return (0);
}
