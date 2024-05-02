/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:03:13 by soljeong          #+#    #+#             */
/*   Updated: 2024/04/30 20:29:35 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

t_arg *arg_init(int argc, char *argv[])
{
	t_arg	*arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(t_arg));
	if (!arg)
		exit(1);
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->end_flag = IS_NOT_END;
	arg->start_time = get_time();
	if (argc == 5)
		arg->num_of_must_eat = -1;
	else if (argc == 6)
		arg->num_of_must_eat = ft_atoi(argv[5]);
	arg->fork_mutex = malloc(sizeof(pthread_mutex_t *) * arg->num_of_philo);
	arg->fork = malloc(sizeof(int) * arg->num_of_philo);
	while (i < arg->num_of_philo)
	{
		arg->fork[i] = NOT_IN_USE;
		arg->fork_mutex[i] = malloc(sizeof(pthread_mutex_t ));
		pthread_mutex_init(arg->fork_mutex[i], NULL);
		i++;
	}
	arg->print_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(arg->print_mutex, NULL);
	return (arg);
}

int print_check(t_arg *arg)
{
	int print_value;

	pthread_mutex_lock(arg->print_mutex);
	print_value = arg->print_value;
	pthread_mutex_unlock(arg->print_mutex);
	return print_value;
}

int	fork_check(t_arg *arg, int fork)
{
	pthread_mutex_lock(arg->fork_mutex[fork]);
	if (arg->fork[fork] == NOT_IN_USE)
	{
		pthread_mutex_unlock(arg->fork_mutex[fork]);
		return NOT_IN_USE;
	}
	pthread_mutex_unlock(arg->fork_mutex[fork]);
	return IN_USE;
}

void	thread_philo(t_philo *philo)
{

	t_arg *arg;

	arg = philo->arg;
	//if (philo->philo_idx % 2 == 0 && philo->philo_idx == 1)
	//	ft_msleep(arg, arg->time_to_eat / 2);
	if (philo->philo_idx % 2 == 0)
		ft_msleep(arg, arg->time_to_eat);
	while(1)
	{
		if (arg->end_flag == IS_END)
			return(0) ;
		//if (get_time() - philo->last_eat_time >= arg->time_to_die)
		//{
		//	print_philo(arg, philo, "died", get_time());
		//	exit(0);
		//}
		if (fork_check(arg, philo->left) == NOT_IN_USE)
		{
			pthread_mutex_lock(philo->arg->fork_mutex[philo->left]);
			philo->arg->fork[philo->left] = IN_USE;
			print_philo(arg,philo,"has taken a fork", get_time());
			while (1)
			{
				//if ( get_time() - philo->last_eat_time >= arg->time_to_die)
				//{
				//	print_philo(arg, philo, "died", get_time());
				//	exit(0);
				//}
				usleep(100);
				if (fork_check(arg, philo->right) == NOT_IN_USE)
					break;
				if (arg->end_flag == IS_END)
					exit(0) ;
			}
			//if (philo->arg->fork[philo->right] == NOT_IN_USE)
			//{
				pthread_mutex_lock(philo->arg->fork_mutex[philo->right]);
				philo->arg->fork[philo->left] = IN_USE;
				print_philo(arg,philo,"has taken a fork", get_time());
				print_philo(arg,philo,"is eating", get_time());
				ft_msleep(arg,arg->time_to_eat);
				philo->arg->fork[philo->right] = NOT_IN_USE;
				pthread_mutex_unlock(philo->arg->fork_mutex[philo->right]);
			//}
			philo->arg->fork[philo->left] = NOT_IN_USE;
			pthread_mutex_unlock(philo->arg->fork_mutex[philo->left]);
			philo->last_eat_time = get_time(); // -> last eat에서 문제가 있음 얘를 뮤텍스로 걸수도 없고
			philo->num_eat++;
			if (philo->num_eat == philo->arg->num_of_must_eat)
			{
				return ;
			}
			print_philo(arg,philo,"is sleeping", get_time());
			ft_msleep(arg,arg->time_to_sleep);
			print_philo(arg,philo,"is thinking", get_time());
		}
	}
}

void	monitoring_thread(t_philo **philos)
{
	int	i;
	int num;

	i = 0;
	num = philos[0]->arg->num_of_philo;
	//bit 연산해야될듯...??
	while (1)
	{
		usleep(100);
		if (get_time() - philos[i]->last_eat_time >= philos[i]->arg->time_to_die)
		{
			print_philo(philos[i]->arg, philos[i], "is died", get_time());
			philos[i]->arg->end_flag = IS_END; 
			 // print에 대한 락을 걸고, 락을 풀지 않기.
		}
		if (philos[i]->arg->end_flag == IS_END)
			break;
		i++;
		if (i >= num)
			i = 0;
	}
}

int main (int argc, char *argv[])
{
	t_philo		**philos;
	int			idx;
	t_arg		*arg;
	pthread_t	monitor;

	if (argc != 5 && argc != 6)
	{
		write(2,"error\n",6);
		exit(1);
	}
	arg = arg_init(argc, argv);
	idx = 0;
	if (!arg)
		exit(1);
	philos = malloc(sizeof(t_philo *) * arg->num_of_philo);
	int i = 0;
	monitor = malloc(sizeof(pthread_t));
	while (i < arg->num_of_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->philo_idx = i + 1;
		philos[i]->last_eat_time = get_time();
		philos[i]->num_eat = 0;
		philos[i]->left = i;
		philos[i]->right = (i + 1) % arg->num_of_philo;
		philos[i]->arg = arg;
		philos[i]->thread = malloc(sizeof(pthread_t));
		pthread_create(&(philos[i]->thread),NULL,(void *)thread_philo,(void *)philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, (void *)monitoring_thread, philos);
	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_join(&(philos[i]->thread), NULL);
		i++;
	}
	pthread_join(&monitor, NULL);
	while (1)
		;
	// pthread_join해서 기다렸다가 회수함
	//pthread_t thread_t;
	// thread르ㄹ 철학자만큼 만들어...
	// fork는 뮤텍스로 철학자만큼 만들어
	// fork 배열을 arg구조체에 넣고
	// 양옆에 있는애만 집을 수 있게 함.
	// 철학자가 갖고 있어야 하는애는
	// 보인 쓰레드, 양쪽 포크, 최근 먹은 시간, <- 얘 계속모니터랑하면서 어느정도 시간 지나면 죽여야함
	// 몇번 먹었는지, 정도...? 고 철학자 구조체를 배열로 갖고 있어ㅡㅁ!
	return (0);
}

