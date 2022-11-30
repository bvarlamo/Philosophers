/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:54:00 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/02/24 14:44:23 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

void	print(int i, t_philo *pt)
{
	pthread_mutex_lock(&pt->dt->check);
	if (i == 0 && *pt->dt->flag)
		printf("%lld %d has taken left fork\n", get_t() - pt->dt->time, pt->id);
	else if (i == 1 && *pt->dt->flag)
		printf("%lld %d has taken right fork\n", get_t() - pt->dt->time, pt->id);
	else if (i == 2 && *pt->dt->flag)
		printf("%lld %d is eating\n", get_t() - pt->dt->time, pt->id);
	else if (i == 3 && *pt->dt->flag)
		printf("%lld %d is sleeping\n", get_t() - pt->dt->time, pt->id);
	else if (i == 4 && *pt->dt->flag)
		printf("%lld %d is thinking\n", get_t() - pt->dt->time, pt->id);
	else if (i == 5 && *pt->dt->flag)
		printf("%lld %d died\n", get_t() - pt->dt->time, pt->id);
	else if (i == 6 && *pt->dt->flag)
		printf("%lld %d put down left fork\n", get_t() - pt->dt->time, pt->id);
	else if (i == 7 && *pt->dt->flag)
		printf("%lld %d put down right fork\n", get_t() - pt->dt->time, pt->id);
	pthread_mutex_unlock(&pt->dt->check);
}

void	dt_init(char **argv, t_data *dt, t_philo *ptr)
{
	int	i;

	dt->mutex = malloc(sizeof(pthread_mutex_t) * (ft_atoi(argv[1])));
	dt->flag = malloc(sizeof(int));
	dt->forks = malloc(sizeof(int) * (ft_atoi(argv[1])));
	pthread_mutex_init(&dt->check, NULL);
	dt->flag[0] = 1;
	dt->p_count = ft_atoi(argv[1]);
	dt->i = 1;
	dt->ttd = ft_atoi(argv[2]);
	dt->tte = ft_atoi(argv[3]);
	dt->tts = ft_atoi(argv[4]);
	dt->m_eat = -1;
	if (argv[5])
		dt->m_eat = ft_atoi(argv[5]);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&dt->mutex[i], NULL);
		pthread_mutex_init(&ptr[i].eat, NULL);
		dt->forks[i] = 1;
		i++;
	}
}

void	init(char **argv)
{
	int				i;
	t_philo			*ptr;
	t_data			dt;

	ptr = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	dt_init(argv, &dt, ptr);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		ptr[i].id = i + 1;
		ptr[i].l_fork = &dt.forks[i];
		ptr[i].r_fork = &dt.forks[(i + 1) % ft_atoi(argv[1])];
		ptr[i].l_mutex = &dt.mutex[i];
		ptr[i].r_mutex = &dt.mutex[(i + 1) % ft_atoi(argv[1])];
		ptr[i].dt = &dt;
		ptr[i].e_count = 0;
		i++;
	}
	create_threads(ft_atoi(argv[1]), ptr);
	free(dt.mutex);
	free(ptr);
	free(dt.flag);
	free(dt.forks);
	pthread_mutex_destroy(&dt.check);
}

long long	get_t(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000);
}
