#include "philo.h"

int	ft_atoi(const char *str)
{
	int					minus;
	unsigned long long	num;

	num = 0;
	minus = 1;
	while (*str == '\t' || *str == '\n' || *str == ' ' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -minus;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - 48);
		if (num > 9223372036854775807 && minus == 1)
			return (-1);
		else if (num > 9223372036854775807 && minus == -1)
			return (0);
		str++;
	}
	return (minus * (int)num);
}
