SRCS = src/main.c src/error.c src/ft_split.c src/ft_strjoin_free.c src/get_map_info.c \
		src/get_texture.c src/init.c src/key_press.c src/list.c src/parse_color.c src/parse_map.c \
		src/parse.c src/control.c src/pathfind.c src/player_position.c src/ray.c src/texture.c src/utils.c src/utils2.c src/utils3.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c mallocCollector/mallocCollector.c src/wall_check.c
OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -L./minilibx -lmlx -framework OpenGL -framework AppKit -lm
MLX = ./minilibx/libmlx.a
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(MLX):
	@$(MAKE) -C minilibx

clean:
	@$(MAKE) -C minilibx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re