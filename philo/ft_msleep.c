/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:05:27 by soljeong          #+#    #+#             */
/*   Updated: 2024/04/30 19:07:06 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "unistd.h"

void	ft_msleep(t_arg *arg, int sleep_time)
{
	(void)arg;
	long start_time = get_time();
	while (1)
	{
		if (get_time() - start_time  >= sleep_time)
			break;
		usleep(100);
	}
}