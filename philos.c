/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:04:53 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/02/24 15:11:10 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*time_loop(void *ptr)
{
	t_philo	*pt;

	pt = ptr;
	while (pt->dt->ttd > get_t() - pt->st && pt->dt->i < pt->dt->p_count + 1)
		usleep(1000);
	pthread_mutex_lock(&pt->eat);
	if (*pt->dt->flag)
	{
		*pt->dt->flag = 0;
		if (pt->dt->i == 1)
			printf("%lld %d died\n", get_t() - pt->dt->time, pt->id);
		else
			printf("%lld All philosophers ate\n", get_t() - pt->dt->time);
	}
	pthread_mutex_unlock(&pt->eat);
	return (NULL);
}

void	eating(t_philo *pt)
{
	pthread_mutex_lock(pt->l_mutex);
	print(0, pt);
	*pt->l_fork = 1;
	pthread_mutex_lock(pt->r_mutex);
	print(1, pt);
	*pt->r_fork = 1;
	pthread_mutex_lock(&pt->eat);
	pt->st = get_t();
	pthread_mutex_unlock(&pt->eat);
	print(2, pt);
	while (get_t() < pt->st + pt->dt->tte && *pt->dt->flag)
		usleep(1000);
	pt->e_count += 1;
	if (pt->dt->m_eat >= 0 && pt->e_count == pt->dt->m_eat)
		pt->dt->i += 1;
	pthread_mutex_unlock(pt->l_mutex);
	print(6, pt);
	pthread_mutex_unlock(pt->r_mutex);
	print(7, pt);
}

void	*thinking(void *ptr)
{
	t_philo	*pt;

	pt = ptr;
	if (pt->dt->p_count == 1 || !pt->dt->m_eat)
		usleep(pt->dt->ttd * 1000);
	while (*pt->dt->flag)
	{
		print(4, pt);
		eating(pt);
		print(3, pt);
		while (get_t() < pt->st + pt->dt->tte + pt->dt->tts && *pt->dt->flag)
			usleep(1000);
	}
	pthread_mutex_destroy(&pt->dt->mutex[pt->id - 1]);
	pthread_mutex_destroy(&pt->eat);
	pthread_mutex_destroy(pt->l_mutex);
	pthread_mutex_destroy(pt->r_mutex);
	return (NULL);
}

void	create_threads(int philo_count, t_philo *ptr)
{
	int		i;
	int		y;

	y = 0;
	ptr[0].dt->time = get_t();
	while (y < 2)
	{
		i = y;
		while (i < philo_count)
		{	
			ptr[i].st = get_t();
			pthread_create(&ptr[i].t1, NULL, &time_loop, &ptr[i]);
			pthread_create(&ptr[i].t, NULL, &thinking, &ptr[i]);
			i += 2;
		}
		usleep(10000);
		y++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_join(ptr[i].t1, NULL);
		pthread_join(ptr[i].t, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	y;

	if (argc < 5 || argc > 6 || !ft_atoi(argv[1]))
		return (write(1, "error\n", 6));
	i = 1;
	while (argv[i])
	{
		y = 0;
		while (argv[i][y])
		{
			if (argv[i][y] < '0' || argv[i][y] > '9')
				return (write(1, "error\n", 6));
			y++;
		}
		i++;
	}
	init(argv);
	return (0);
}
