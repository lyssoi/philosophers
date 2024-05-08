/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:53:47 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/08 17:58:21 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	print_philo(t_arg *arg, t_philo *philo, char *msg)
{

	(void)time;
	pthread_mutex_lock(arg->print_mutex);
	if (end_flag_check(arg) == IS_END && ft_strncmp(msg, "is died", 8) != 0)
	{
		pthread_mutex_unlock(arg->print_mutex);
		return ;
	}
	printf("%ld %d %s\n", (get_time() - arg->start_time), philo->philo_idx, msg);
	pthread_mutex_unlock(arg->print_mutex);
}
