/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:23 by soljeong          #+#    #+#             */
/*   Updated: 2024/04/29 19:29:17 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>

typedef struct s_arg {
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
	pthread_mutex_t **fork;
} t_arg;

typedef struct s_philo {
	int	philo_idx;
	pthread_t thread;
	//thread
	//forkid
	double last_eat;
	int	num_eat;
} t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif