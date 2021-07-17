#include "philo.h"

void 	food_control(t_philo *ph, int *full, int i)
{
	if (ph[0].all->num_of_meal != -1 && \
				(ph[i].num_eat == ph[0].all->num_of_meal \
				|| ph[i].num_eat > ph[0].all->num_of_meal))
		(*full)++;
}

void	*life_check(void *p)
{
	t_philo		*ph;
	int			i;
	int			full_philos;

	ph = (t_philo *)p;
	while (1)
	{
		i = -1;
		full_philos = 0;
		while (++i < ph[0].all->number_of_philo)
		{
			if ((get_time() - ph[i].last_ate) > (ph[0].all->time_to_die))
			{
				pthread_mutex_lock(&ph[0].all->flag_lock);
				ph[0].all->flag = 1;
				pthread_mutex_unlock(&ph[0].all->flag_lock);
				custom_print(&ph[i], \
				(long int)(get_time() - ph->all->start_time), "died\n", 2);
				return (NULL);
			}
			food_control(ph, &full_philos, i);
		}
		if (full_philos == ph[0].all->number_of_philo)
		{
			ph[0].all->flag = 1;
			pthread_mutex_lock(&ph->all->print);
			return (NULL);
		}
	}
}

void	philosopher_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	custom_print(ph, (long int)(get_time() - ph->all->start_time),
		 "has taken a left fork\n", 1);
	pthread_mutex_lock(ph->right_fork);
	custom_print(ph, (long int)(get_time() - ph->all->start_time),
		 "has taken a right fork\n", 1);
	custom_print(ph, (long int)(get_time() - ph->all->start_time),
		 "is eating\n", 1);
	ph->last_ate = get_time();
	custom_sleep(ph->all->time_to_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	ph->num_eat++;
}

void	*routine(void *i)
{
	t_philo	*ph;

	ph = (t_philo *)i;
	ph->last_ate = get_time();
	while (ph->all->flag == 0)
	{
		philosopher_eats(ph);
		custom_print(ph, (long int)(get_time() - ph->all->start_time),
			 "is sleeping\n", 1);
		custom_sleep(ph->all->time_to_sleep);
		custom_print(ph, (long int)(get_time() - ph->all->start_time),
			 "is thinking\n", 1);
	}
	return (NULL);
}

void 	threads_init(t_philo *philo)
{
	pthread_t	checker;
	int			i;

	if (pthread_mutex_init(&philo->all->print, NULL))
		ft_error_exit("Failed to create mutex print");
	philo->ph = malloc(sizeof(pthread_t) * philo->all->number_of_philo);
	if (!philo->ph)
		ft_error_exit("Malloc error");
	i = -1;
	philo->all->start_time = get_time();
	while (++i < philo->all->number_of_philo)
	{
		if (pthread_create(&philo->ph[i], NULL, &routine, (void *) &philo[i]))
			ft_free_error("Pthread_create error", philo);
		usleep(50);
	}
	if (pthread_create(&checker, NULL, &life_check, (void *)&philo[0]))
		ft_free_error("Pthread_create error", philo);
	philo->all->death_checker = checker;
}
