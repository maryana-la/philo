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

typedef struct	s_philo
{
	int	number_of_philo;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int num_of_meal;
}				t_philo;

int	check_args_valid(int argc, char **argv);


/*
 * 	libft utils
 */

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif //PHILO_PHILO_H
