//
// Created by Ragwyle Chelsea on 7/8/21.
//

#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct	s_all
{
	int			number_of_philo;
	long int	time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meal;
	long int	start_time;
	int 		num_of_full_philos;
	int 		flag_death;
	struct timeval start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
//	pthread_mutex_t death;
//	pthread_mutex_t time;
	pthread_t 	checker;
}				t_all;

typedef struct s_philo
{
	int 		num;
	long int	last_ate;
	int 		num_eat;
	struct s_all	*all;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}				t_philo;



int	check_args_valid(int argc, char **argv);


/*
 * 	libft utils
 */

int	ft_isdigit(int c);
int	ft_atoi(const char *str);


long int	time_calculate(void);
void	custom_sleep(long int time);

#endif //PHILO_PHILO_H
