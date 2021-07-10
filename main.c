//
// Created by Ragwyle Chelsea on 7/8/21.
//

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

void init_structure(t_all *all, int argc, char **argv)
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

void *routine(void *i)
{
	t_philo	*ph;


	ph = (t_philo *)i;
	while (1)
	{
//eating
		pthread_mutex_lock(ph->left_fork);
		gettimeofday(&ph->all->end, NULL);
		printf("%ld ms %d has taken a left fork\n", (((ph->all->end.tv_sec * 1000) + (ph->all->end.tv_usec / 1000)) - ph->all->start_time), ph->num);
		pthread_mutex_lock(ph->right_fork);
		gettimeofday(&ph->all->end, NULL);
		printf("%ld ms %d has taken a right fork\n", (((ph->all->end.tv_sec * 1000) + (ph->all->end.tv_usec / 1000)) - ph->all->start_time),  ph->num);
		printf("%ld ms %d is eating\n", (((ph->all->end.tv_sec * 1000) + (ph->all->end.tv_usec / 1000)) - ph->all->start_time), ph->num);
		usleep(ph->all->time_to_eat);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);

//	sleeping
		gettimeofday(&ph->all->end, NULL);
		printf("%ld ms %d is sleeping\n", (((ph->all->end.tv_sec * 1000) + (ph->all->end.tv_usec / 1000)) - ph->all->start_time), ph->num);
		usleep(ph->all->time_to_sleep);

//thinking
		gettimeofday(&ph->all->end, NULL);
		printf("%ld ms %d is thinking\n", (((ph->all->end.tv_sec * 1000) + (ph->all->end.tv_usec / 1000)) - ph->all->start_time), ph->num);
		usleep(100);
	}
	return (0);
}

int main (int argc, char **argv)
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
		pthread_join(ph[i], NULL);


	gettimeofday(&all.end, NULL);
	printf("Time to execute program %ld milliseconds\n", (((all.end.tv_sec * 1000) + (all.end.tv_usec / 1000)) - ((all.start.tv_sec * 1000) + (all.start.tv_usec / 1000))));
}




// time explanation
//	struct timeval tv;
//	struct timezone tz;
//	printf("TimeZone-1 = %d\n", tz.tz_minuteswest);
//	printf("TimeZone-2 = %d\n", tz.tz_dsttime);
//	// Cast members as specific type of the members may be various
//	// signed integer types with Unix.
//	printf("TimeVal-3  = %lld\n", (long long) tv.tv_sec); //seconds from the beginning or era
//	printf("TimeVal-4  = %lld\n", (long long) tv.tv_usec); //доп микросекунды после вычисления количества секунд с начала эпохи
//
//	// Form the seconds of the day
//	long hms = tv.tv_sec % 86400; //seconds per day
//	hms += tz.tz_dsttime * 3600; //sec per hour
//	hms -= tz.tz_minuteswest * 60; //sec per minute
//	// mod `hms` to insure in positive range of [0...SEC_PER_DAY)
//	hms = (hms + 86400) % 86400;
//
//	// Tear apart hms into h:m:s
//	int hour = hms / 3600;
//	int min = (hms % 3600) / 60;
//	int sec = (hms % 3600) % 60; // or hms % SEC_PER_MIN
//	printf("Current local time: %d:%02d:%02d\n", hour, min, sec);
