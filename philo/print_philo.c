/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:53:47 by soljeong          #+#    #+#             */
/*   Updated: 2024/04/30 20:10:08 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_arg *arg, t_philo *philo, char *msg, long time)
{
	printf("%ld %d %s\n",time - arg->start_time, philo->philo_idx, msg);
	// 현재 타임은 했다 치고...
}