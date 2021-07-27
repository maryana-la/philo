/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:52:47 by rchelsea          #+#    #+#             */
/*   Updated: 2021/07/27 15:52:48 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	long int		current;
	struct timeval	now;

	gettimeofday(&now, NULL);
	current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (current);
}

void	custom_sleep(long int time)
{
	long int		begin;
	long int		current;
	struct timeval	begin_time;
	struct timeval	current_time;

	gettimeofday(&begin_time, NULL);
	begin = (begin_time.tv_sec * 1000 + begin_time.tv_usec / 1000) * 1000;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = \
			(current_time.tv_sec * 1000 + current_time.tv_usec / 1000) * 1000;
		if (current - begin < (long int)(time))
		{
			usleep(500);
			continue ;
		}
		break ;
	}
}

void	ft_error_exit(char *error)
{
	printf("%s\n", error);
	exit (1);
}

void	ft_free_error(char *error, t_philo *philo)
{
	if (philo->all->forks)
		free(philo->all->forks);
	if (philo->ph)
		free(philo->ph);
	if (philo)
		free(philo);
	printf("%s\n", error);
	exit (1);
}

void	custom_print(t_philo *ph, long int time, char *message, int type)
{
	pthread_mutex_lock(&ph->all->flag_lock);
	if (!ph->all->flag)
	{
		pthread_mutex_lock(&ph->all->print);
		printf("%ld\tms\t%d\t%s", time, ph->num, message);
		pthread_mutex_unlock(&ph->all->print);
	}
	pthread_mutex_unlock(&ph->all->flag_lock);
	if (type == 2)
	{
		pthread_mutex_lock(&ph->all->print);
		printf("%ld\tms\t%d\t%s", time, ph->num, message);
		pthread_mutex_unlock(&ph->all->print);
	}
}
