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
	all->time_to_die = (long int) ft_atoi(argv[2]);
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
	all->flag_dead = 0;
}

void	*death_check(void *p)
{
	t_philo		*ph;
	pthread_mutex_t msg;
	int i;
	int full_philos;
	long int current;


	pthread_mutex_init(&msg, NULL);
	ph = (t_philo *)p;
	while (1)
	{
		i = -1;
		full_philos = 0;
		current = time_calculate();
		while (++i < ph[0].all->number_of_philo)
		{
			if ((current - ph[i].last_ate) > (ph[0].all->time_to_die))
			{
				ph[0].all->flag_dead = 1;
				custom_print(ph, (int)(time_calculate() - ph->all->start_time), "died\n", 2);
				return ((void *)1);
			}
			if(ph[0].all->num_of_meal != -1 && (ph[i].num_eat == ph[0].all->num_of_meal || ph[i].num_eat > ph[0].all->num_of_meal))
				full_philos++;
		}
		if (full_philos == ph[0].all->number_of_philo)
		{
			custom_print(ph, (int)(time_calculate() - ph->all->start_time), "Everybody has eaten\n", 2);
			return ((void *)2);
		}
	}
}

void	*routine(void *i)
{
	t_philo	*ph;

	ph = (t_philo *)i;

	ph->last_ate = time_calculate();
//	if (ph->num % 2 == 0)
//		usleep(20);
//	while (((ph->num_eat <= ph->all->num_of_meal && ph->all->num_of_meal != -1)
//		|| ph->all->num_of_meal == -1))
	while (1)
	{
//eating
//		if (ph->num % 2)
//		{
//			pthread_mutex_lock(ph->right_fork);
//			custom_print(ph, (int)(time_calculate() - ph->all->start_time), " has taken a right fork\n");
//			pthread_mutex_lock(ph->left_fork);
//			custom_print(ph, (int)(time_calculate() - ph->all->start_time), " has taken a left fork\n");
//			custom_print(ph, (int)(time_calculate() - ph->all->start_time), " is eating\n");
//			ph->last_ate = time_calculate();
//			custom_sleep(ph->all->time_to_eat);
//			pthread_mutex_unlock(ph->right_fork);
//			pthread_mutex_unlock(ph->left_fork);
//			ph->num_eat++;
//		}
//		else
//		{
			pthread_mutex_lock(ph->left_fork);
			custom_print(ph, (int)(time_calculate() - ph->all->start_time), "has taken a left fork\n", 1);
			pthread_mutex_lock(ph->right_fork);
			custom_print(ph, (int)(time_calculate() - ph->all->start_time), "has taken a right fork\n", 1);
			custom_print(ph, (int)(time_calculate() - ph->all->start_time), "is eating\n", 1);
			ph->last_ate = time_calculate();
			custom_sleep(ph->all->time_to_eat);
			pthread_mutex_unlock(ph->left_fork);
			pthread_mutex_unlock(ph->right_fork);
			ph->num_eat++;
//		}
//	sleeping
//		pthread_mutex_lock(ph->all->print);
		custom_print(ph, (int)(time_calculate() - ph->all->start_time), " is sleeping\n", 1);
//		pthread_mutex_unlock(ph->all->print);
		custom_sleep(ph->all->time_to_sleep);

//thinking
//		pthread_mutex_lock(ph->all->print);
		custom_print(ph, (int)(time_calculate() - ph->all->start_time), " is thinking\n", 1);
//		pthread_mutex_unlock(ph->all->print);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all all;
	int		i;
	pthread_mutex_t printing;



	if (check_args_valid(argc, argv) < 0)
		exit (-1);
	init_structure(&all, argc, argv);

	pthread_mutex_init(&printing, NULL);
	all.print =  &printing;

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
	pthread_t 	checker;
	pthread_t	*ph;
	ph = malloc(sizeof(pthread_t) * all.number_of_philo);
	i = 0;

	all.start_time = time_calculate();
	while(i < all.number_of_philo)
	{
		pthread_create(&ph[i], NULL, &routine, (void *) &philo[i]);
		usleep(20);
		i++;
	}

	pthread_create(&checker, NULL, &death_check, (void *)&philo[0]);
	// threads close

	i = -1;
//	while(++i < all.number_of_philo)
//		pthread_join(ph[i], NULL);
	while(++i < all.number_of_philo)
		pthread_detach(ph[i]);
//	usleep(50);
	pthread_mutex_unlock(philo->all->print);
	pthread_join(checker, NULL);
	pthread_detach(checker);
	i = -1;
	while(++i < all.number_of_philo)
		pthread_mutex_destroy(&all.forks[i]);
	pthread_mutex_destroy(philo->all->print);

	return 0;
}
