/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:23 by soljeong          #+#    #+#             */
/*   Updated: 2024/04/30 18:23:39 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <stdio.h>

enum {
	IN_USE,
	NOT_IN_USE
};

enum {
	IS_END,
	IS_NOT_END
};

typedef struct s_arg {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	long			start_time;
	int				end_flag;
	int				*fork;
	pthread_mutex_t	**fork_mutex;
	pthread_mutex_t *print_mutex;
	int				print_value;
} t_arg;

typedef struct s_philo {
	int	philo_idx;

	pthread_t thread;
	int	left;
	int	right;
	//thread
	//forkid
	long	last_eat_time; // ㅁㅏ지막 먹은 시간을 알아야 죽거나 할 수 있으니까!
	int	num_eat;
	t_arg	*arg;
} t_philo;

// left라ㅇ right은... 

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	print_philo(t_arg *arg, t_philo *philo, char *msg, long time);
long	get_time();
void	ft_msleep(t_arg *arg, int sleep_time);

#endif