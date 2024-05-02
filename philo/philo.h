/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:23 by soljeong          #+#    #+#             */
/*   Updated: 2024/05/02 20:30:17 by soljeong         ###   ########.fr       */
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
	IS_NOT_END,
	IS_END,
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
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	*thread_make_mutex;
} t_arg;

typedef struct s_philo {
	int				philo_idx;
	pthread_t		thread;
	int				left;
	int				right;
	long			last_eat_time;
	int				num_eat;
	t_arg			*arg;
	pthread_mutex_t	*last_eat_time_nutex;
	pthread_mutex_t	*num_eat_mutex;
} t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	print_philo(t_arg *arg, t_philo *philo, char *msg, long time);
long	get_time();
void	ft_msleep(t_philo *philo, int sleep_time);
int		print_check(t_arg *arg);
int		end_flag_check(t_arg *arg);
int		fork_check(t_arg *arg, int fork);
int		end_flag_check_in_thread(t_philo *philo, int left_use, int right_use);
void	thread_philo(t_philo *philo);
long	last_eat_check(t_philo *philo);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	mutex_end_change(pthread_mutex_t *mutex, int *flag);
int		right_fork_check(t_arg *arg, t_philo *philo);
void	fork_chage_use(t_philo *philo, int idx);
void	fork_chag_not_use(t_philo *philo, int idx);
int		num_eat_check(t_philo *philo);

#endif