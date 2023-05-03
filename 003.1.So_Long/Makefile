NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Iheaders/

SOURCE := main.c map.c map_2.c map_reading.c graphics.c controls.c
GETNEXTLINE := get_next_line/*c
LIBFT := libft/ft_*.c
FTPRINTF := ft_printf/*c
LIBRARY := -Lminilibx -lmlx -framework OpenGL -framework AppKit
MINILIBX := minilibx/

all:
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(SOURCE) $(FTPRINTF) $(LIBFT) $(GETNEXTLINE) $(LIBRARY) -o $(NAME)

clean:
	@rm -f  *.o

fclean: clean
		make clean -C $(MINILIBX)
		rm -rf $(NAME)

re: fclean all
