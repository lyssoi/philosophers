/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:05:27 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:54:15 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "unistd.h"

void	ft_msleep(t_philo *philo, int sleep_time)
{
	long	start_time;
	long	last_eat_time;
	long	curr_time;

	start_time = get_time();
	last_eat_time = last_eat_check(philo);
	if (start_time + sleep_time - last_eat_time < philo->arg->time_to_die)
		usleep(sleep_time * 900);
	else
		usleep((get_time() - last_eat_time) * 900);
	while (1)
	{
		curr_time = get_time();
		if (curr_time - start_time >= sleep_time)
			return ;
		if (curr_time - last_eat_time >= philo->arg->time_to_die)
		{
			mutex_end_change(philo->arg->end_mutex, &(philo->arg->end_flag));
			return ;
		}
		usleep(100);
	}
}
