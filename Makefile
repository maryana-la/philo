all:
	gcc -g main.c utils.c ft_isdigit.c ft_atoi.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c -pthread -ophilo

clean:
	rm philo