#ifndef SO_LONG_H
#define SO_LONG_H
typedef struct l_index
{
	int	i;
	int	j;
	int	k;
} t_index;

typedef struct l_start
{
    int     map_height;
    int     map_width;
    int     collectables;
    int     read_count;
    int     counter;
    int     y_axis;
    int     x_axis;

    char    **map;
    char    *maplocation;

    // init oyun ıcın her seyi hazir edip adres dondurur
    void *mlxpointer;
    // pencereyi hazir ediyoruz (gerekli boyutu vs vererek)
    void *winpointer;
    void *floor;
    void *barrier;
    void *player;
    void *exit;
    void *collectable;

	t_index index;
} t_game;

#include <stdio.h>
#include "./ft_printf/ft_printf.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "./minilibx/mlx.h"
#include <fcntl.h>
#include <unistd.h>

int exit_point(t_game *data);
int controls_working(int command, t_game *data);

void    err_msg(char *err);
void    ber_control(char *map_name);
void    wall_control(t_game *data);
void    map_control(char *map_name, t_game *data);
void    map_reading(t_game *data);
void    tmp_control(char *map_name);
void    map_processing(t_game *data);
void    images_in_game(t_game *data);
void	placeholder(t_game *data, int x, int y);
void    place_collectable(t_game *data, int height, int width);
void    place_player(t_game *data, int height, int width);
void    adding_in_graphics(t_game *data);
void    map_bug(t_game *data);

#endif
