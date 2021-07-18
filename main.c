#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;
	t_philo	*philo;

	philo = NULL;
	check_args_valid(argc, argv);
	init_structure(&all, argc, argv);
	philo = philos_init(&all);
	threads_init(philo);
	threads_close(philo);
	return (0);
}

int	check_args_valid(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		write(1, "Wrong number of arguments\n", 27);
		exit (1);
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
				exit (1);
			}
		}
	}
	return (0);
}

void	init_structure(t_all *all, int argc, char **argv)
{
	int	i;

	all->number_of_philo = ft_atoi(argv[1]);
	all->time_to_die = (long int) ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]) * 1000;
	all->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		all->num_of_meal = ft_atoi(argv[5]);
	else
		all->num_of_meal = -1;
	if (all->number_of_philo < 1 || all->time_to_die < 1 || all->time_to_eat < 1
		|| all->time_to_sleep < 1 || all->num_of_meal == 0)
	{
		write(1, "Argument is too small\n", 22);
		exit (1);
	}
	all->flag = 0;
	pthread_mutex_init(&all->flag_lock, NULL);
	all->forks = malloc(sizeof(pthread_mutex_t) * (all->number_of_philo + 1));
	i = -1;
	while (++i < all->number_of_philo)
		if (pthread_mutex_init(&all->forks[i], NULL))
			ft_error_exit("Failed to create mutex fork");
}

t_philo	*philos_init(t_all *all)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * (all->number_of_philo + 1));
	if (!philo)
		return (NULL);
	while (++i < all->number_of_philo)
	{
		philo[i].num = i + 1;
		philo[i].last_ate = 0;
		philo[i].num_eat = 0;
		philo[i].all = all;
		if ((i + 1) != all->number_of_philo)
		{
			philo[i].left_fork = &all->forks[i];
			philo[i].right_fork = &all->forks[i + 1];
		}
		else
		{
			philo[i].left_fork = &all->forks[i];
			philo[i].right_fork = &all->forks[0];
		}
	}
	return (philo);
}

void	threads_close(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->all->number_of_philo)
		pthread_join(philo->ph[i], NULL);
	pthread_join(philo->all->death_checker, NULL);
	pthread_detach(philo->all->death_checker);
	i = -1;
	while (++i < philo->all->number_of_philo)
		pthread_mutex_destroy(&philo->all->forks[i]);
	pthread_mutex_destroy(&philo->all->print);
	if (philo->all->forks)
		free(philo->all->forks);
	if (philo->ph)
		free(philo->ph);
	if ((philo))
		free(philo);
}
