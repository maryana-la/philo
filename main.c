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

void	test()
{
	int i;

	for (i = 0; i < 10; i++)
	{
		printf("test_func %d\n", i);
		usleep(5);
	}
}

int main (int argc, char **argv)
{
	t_philo philo;
	struct timeval start;
	struct timeval end;
	struct timezone tz;

	gettimeofday(&start, &tz);
	if (check_args_valid(argc, argv) < 0)
		exit (-1);

	//todo check for min max value

	philo.number_of_philo = ft_atoi(argv[1]);
	if (philo.number_of_philo < 1)
	{
		write(1, "Wrong number of philosophers\n", 29);
		return (-1);
	}
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.num_of_meal = ft_atoi(argv[5]);
	else
		philo.num_of_meal = -1;

	pthread_t p1;
	pthread_t p2;
	pthread_create(&p1, NULL, (void *)test, NULL);
	pthread_create(&p2, NULL, (void *)test, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);


	gettimeofday(&end, &tz);
	printf("Time to execute program %ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
	return (0);
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
