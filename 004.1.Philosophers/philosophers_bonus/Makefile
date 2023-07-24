NAME = philo

INC 	= philo_bonus.h

SRC		=	*.c

CC 		= gcc

FLAGS	= -Wall -Wextra -Werror ##-pthread -fsanitize=thread -g

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
