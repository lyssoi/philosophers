/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soljeong <soljeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:03:13 by soljeong          #+#    #+#             */
/*   Updated: 2024/04/29 19:42:03 by soljeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

double get_time()
{
	double		begin;
	struct timeval tv;

	begin = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
t_arg *arg_init(int argc, char *argv[])
{
	t_arg	*arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(t_arg));
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
if (argc == 5)
		arg->num_of_must_eat = 0;
	else if (argc == 6)
		arg->num_of_must_eat = ft_atoi(argv[5]);
	arg->fork = malloc(sizeof(pthread_mutex_t *) * arg->num_of_philo);
	while (i < arg->num_of_philo)
	{
		phtread_mutex_init(&(arg->fork[i]), NULL);
	}
}

int main (int argc, char *argv[])
{
	t_philo		**philos;
	int	idx;
	t_arg	*arg;

	arg = arg_init(argc, argv);
	idx = 0;
	if (!arg)
		exit(1);
	if (argc != 5 && argc != 6)
	{
		write(2,"error\n",6);
		exit(1);
	}

	

	philos = malloc(sizeof(t_philo) * arg->num_of_philo);
	int i = 0;
	while (i < arg->num_of_philo)
	{
		philos[i]->philo_idx = i;
		philos[i]->last_eat = 	get_time();
		philos[i]->num_eat = 0;
		// 스레드는 추후 만드는 방법을 고려해본다... 함수를 안에 넣어줘야 하기 때문!
		// philos 쓰레드 만들기! 
	}
	//pthread_t thread_t;
	// thread르ㄹ 철학자만큼 만들어...
	// fork는 뮤텍스로 철학자만큼 만들어
	// fork 배열을 arg구조체에 넣고
	// 양옆에 있는애만 집을 수 있게 함.
	// 철학자가 갖고 있어야 하는애는
	// 보인 쓰레드, 양쪽 포크, 최근 먹은 시간, <- 얘 계속모니터랑하면서 어느정도 시간 지나면 죽여야함
	// 몇번 먹었는지, 정도...? 고 철학자 구조체를 배열로 갖고 있어ㅡㅁ!
}

