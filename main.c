#include "philo.h"

int	check_args_valid(int argc, char **argv)
{
	int i;
	int j;

	if (argc < 5 || argc > 6)
	{
		write(1, "Wrong number of arguments\n", 27);
		return (-1);
	}

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(1, "Invalid argument\n", 17);
				return(-1);
			}
		}
	}

	return (0);
}

void	init_structure(t_all *all, int argc, char **argv)
{
	all->number_of_philo = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]) * 1000;
	all->time_to_eat = ft_atoi(argv[3]) * 1000;
	all->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		all->num_of_meal = ft_atoi(argv[5]);
	else
		all->num_of_meal = -1;

	if (all->number_of_philo < 1 || all->time_to_die < 1 || all->time_to_eat < 1 || all->time_to_sleep < 1 || all->num_of_meal == 0)
	{
		write(1, "Argument is too small\n", 22);
		exit (-1);
	}
	gettimeofday(&all->start, NULL);
	all->start_time = (all->start.tv_sec * 1000) + (all->start.tv_usec / 1000);
}

int	time_calculate(t_philo *ph)
{
	long int current;

	gettimeofday(&ph->all->end, NULL);
	current = (ph->all->end.tv_sec * 1000) + (ph->all->end.tv_usec / 1000) - ph->all->start_time;
	return((int)current);
}

void	custom_sleep(long int time)
{
	long int	begin;
	long int	current;
	struct timeval	begin_time;
	struct timeval	current_time;

	gettimeofday(&begin_time, NULL);
	begin = (begin_time.tv_sec * 1000 + begin_time.tv_usec / 1000) * 1000;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) * 1000;
		if (current - begin < (long int)(time))
		{
			usleep(50);
			continue ;
		}
		break ;
	}
}

void	*routine(void *i)
{
	t_philo	*ph;

	ph = (t_philo *)i;
	while (ph->num_eat < ph->all->num_of_meal)
	{
//eating
		if (ph->num % 2)
		{
			pthread_mutex_lock(ph->left_fork);
			printf("%d ms %d has taken a left fork\n", time_calculate(ph), ph->num);
			pthread_mutex_lock(ph->right_fork);
			printf("%d ms %d has taken a right fork\n", time_calculate(ph), ph->num);
			printf("%d ms %d is eating\n", time_calculate(ph), ph->num);
			ph->last_ate = time_calculate(ph);
			custom_sleep(ph->all->time_to_eat);
			ph->num_eat++;
			pthread_mutex_unlock(ph->left_fork);
			pthread_mutex_unlock(ph->right_fork);
		}
		else
		{
			pthread_mutex_lock(ph->right_fork);
			printf("%d ms %d has taken a right fork\n", time_calculate(ph), ph->num);
			pthread_mutex_lock(ph->left_fork);
			printf("%d ms %d has taken a left fork\n", time_calculate(ph), ph->num);
			printf("%d ms %d is eating\n", time_calculate(ph), ph->num);
			custom_sleep(ph->all->time_to_eat);
			ph->num_eat++;
			pthread_mutex_unlock(ph->right_fork);
			pthread_mutex_unlock(ph->left_fork);
		}
//	sleeping
		printf("%d ms %d is sleeping\n", time_calculate(ph), ph->num);
		custom_sleep(ph->all->time_to_sleep);

//thinking
		printf("%d ms %d is thinking\n", time_calculate(ph), ph->num);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all all;
	int		i;



	if (check_args_valid(argc, argv) < 0)
		exit (-1);
	init_structure(&all, argc, argv);

	// forks create
	all.forks = malloc(sizeof(pthread_mutex_t) * all.number_of_philo);
	i = -1;
	while(++i < all.number_of_philo)
		pthread_mutex_init(&all.forks[i], NULL);

	// philosophers init
	t_philo *philo;
	i = -1;
	philo = malloc(sizeof(t_philo) * all.number_of_philo);
	while(++i < all.number_of_philo)
	{
		philo[i].num = i + 1;
		philo[i].last_ate = 0;
		philo[i].num_eat = 0;
		philo[i].all = &all;
		if ((i + 1) != all.number_of_philo)
		{
			philo[i].left_fork = &all.forks[i];
			philo[i].right_fork = &all.forks[i + 1];
		}
		else
		{
			philo[i].left_fork = &all.forks[i];
			philo[i].right_fork = &all.forks[0];
		}
	}

	// threads create
	pthread_t	*ph;
	ph = malloc(sizeof(pthread_t) * all.number_of_philo);
	i = -1;
	gettimeofday(&all.start, NULL);
	while(++i < all.number_of_philo)
	{
		pthread_create(&ph[i], NULL, &routine, (void *)&philo[i]);
		usleep(10);
	}

	// threads close
	i = -1;
	while(++i < all.number_of_philo)
	{
		pthread_join(ph[i], NULL);
//		free(ph[i]);
//		free(&philo[i]);
	}
	return 0;
}
