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
	long int	start_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meal;
	struct timeval start;
	struct timeval end;
	pthread_mutex_t	*forks;
}				t_all;

typedef struct s_philo
{
	int 		last_ate;
	int 		num_eat;
	int 		num;
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

#endif //PHILO_PHILO_H
