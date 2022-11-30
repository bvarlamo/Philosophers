/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:07:31 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/02/24 14:45:26 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				*flag;
	int				*forks;
	int				i;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	int				m_eat;
	int				p_count;
	long			time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	check;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				i;
	int				*l_fork;
	int				*r_fork;
	int				e_count;
	long long		st;
	pthread_t		t;
	pthread_t		t1;
	pthread_mutex_t	eat;
	pthread_mutex_t	*l_mutex;
	pthread_mutex_t	*r_mutex;
	t_data			*dt;
}			t_philo;

int			ft_atoi(const char *str);
long long	get_t(void);
int			ft_isdigit(int c);
void		dt_init(char **argv, t_data *dt, t_philo *ptr);
void		print(int i, t_philo *pt);
void		init(char **argv);
void		create_threads(int philo_count, t_philo *ptr);

#endif