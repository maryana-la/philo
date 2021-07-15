#include "philo.h"

long int	time_calculate(void)
{
	long int current;
	struct timeval now;

	gettimeofday(&now, NULL);
	current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return(current);
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s++ != '\0')
		size++;
	return (size);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putnbr(long nb)
{
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-');
	}
	if (nb < 10)
		ft_putchar(nb + 48);
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}



void custom_print(t_philo *ph, int time, char *message, int type)
{
	pthread_mutex_lock(ph->all->print);
//	if (!ph->all->flag_dead)
//	{
//		ft_putnbr(time);
//		ft_putstr("\tms\t");
//		ft_putnbr(ph->num);
//		ft_putchar('\t');
//		ft_putstr(message);

		printf("%d\tms\t%d\t%s", time, ph->num, message);
//	}
	if (type !=2)
		pthread_mutex_unlock(ph->all->print);
}