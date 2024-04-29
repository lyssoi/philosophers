NAME = philo
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c\
		ft_atoi.c\
		ft_isdigit.c

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	make clean

re: 
	make fclean
	make all

.PHONY : all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^