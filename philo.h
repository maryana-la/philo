/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:52:37 by rchelsea          #+#    #+#             */
/*   Updated: 2021/07/27 15:52:39 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_all
{
	int				number_of_philo;
	long int		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meal;
	long int		begin;
	int				flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	flag_lock;
	pthread_t		death_checker;
}				t_all;

typedef struct s_philo
{
	int				num;
	long int		last_ate;
	int				num_eat;
	t_all			*all;
	pthread_t		*ph;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

/*
 * 	philo
 */

int			main(int argc, char **argv);
int			check_args_valid(int argc, char **argv);
void		init_structure(t_all *all, int argc, char **argv);
t_philo		*philos_init(t_all *all);
void		threads_close(t_philo *philo);

/*
 *  threads
 */

void		*life_check(void *p);
int			check_if_dead(t_philo *ph, int *full_philos, int i);
void		*routine(void *i);
void		philosopher_eats(t_philo *ph);
void		threads_init(t_philo *philo);

/*
 * 	utils
 */

long int	get_time(void);
void		custom_sleep(long int time);
void		custom_print(t_philo *ph, long int time, char *message, int type);
void		ft_error_exit(char *error);
void		ft_free_error(char *error, t_philo *philo);

/*
 * 	libft utils
 */

int			ft_isdigit(int c);
int			ft_atoi(const char *str);

#endif
