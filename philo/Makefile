NAME = philo
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread #-g3 -fsanitize=address

SRCS = main.c\
		ft_atoi.c\
		ft_isdigit.c\
		ft_msleep.c\
		get_time.c\
		print_philo.c\
		mutex_check.c\
		end_flag_check.c\
		thread_philo.c\
		ft_strncmp.c\
		mutex_change.c\
		fork.c\
		init.c\
		init_philo.c\
		monitoring_thread.c\
		free.c\
		free_philo.c\
		eating.c\
		print_error.c

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)
	make clean

re: 
	make fclean
	make all

.PHONY : all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^