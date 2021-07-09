all:
	gcc -g main.c ft_isdigit.c ft_atoi.c -pthread -ophilo

clean:
	rm philo