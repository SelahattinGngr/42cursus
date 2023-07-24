CC = cc
CFLAGS = -Wall -Wextra -Werror ##-pthread -fsanitize=thread -g
RM = rm -rf

NAME = philo
SRC = $(shell find . -name "*.c")

${NAME}:
	${CC} ${CFLAGS} ${SRC} -o ${NAME}

all: ${NAME}

clean:

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re