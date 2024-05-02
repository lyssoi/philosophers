/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:44:58 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/02 19:46:26 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_end_change(pthread_mutex_t *mutex, int *flag)
{
	pthread_mutex_lock(mutex);
	*flag = IS_END;
	pthread_mutex_unlock(mutex);
}