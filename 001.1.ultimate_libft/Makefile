SRCS	= *.c

OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

all : $(NAME)

$(NAME) :
		$(CC) $(FLAGS) -c $(SRCS)
		ar rcs $(NAME) $(OBJS)

%.o : %.c
	$(CC) -c $^

clean :
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re bonus

