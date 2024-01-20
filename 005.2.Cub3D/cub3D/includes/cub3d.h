/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:36:33 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 18:23:36 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include "../mallocCollector/mallocCollector.h"

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

# define FLOOR 0
# define CEILING 1

# define MAX_FD 256

# define TEX_W 64
# define TEX_H 64
# define SCREEN_W 1280
# define SCREEN_H 720

# define BUFFER_SIZE 1024

enum e_key
{
	KEY_ESC = 53,
	KEY_EVENT_PRESS = 2,
	KEY_EVENT_RELEASE = 3,
	KEY_EVENT_EXIT = 17,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124
};

enum e_dir
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

typedef struct s_node
{
	char			*map;
	struct s_node	*next;
}	t_node;

typedef struct s_maplist
{
	int			size;
	t_node		*head;
	t_node		*tail;
}	t_maplist;

typedef struct s_ray
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_ray;

typedef struct s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			img_width;
	int			img_height;
}	t_img;

typedef struct s_game
{
	void				*mlx;
	void				*win;

	int					**buf;
	int					**texture;
	int					map_width;
	int					map_height;
	int					key_a;
	int					key_w;
	int					key_s;
	int					key_d;
	int					key_left;
	int					key_right;
	int					player;
	int					color_flag;
	int					dir_flag;
	int					pos_flag;
	int					floor;
	int					ceiling;

	double				msws;
	double				msad;

	char				**map;

	t_img				img;
	t_ray				ray;
	t_maplist			*list;
	t_mallocCollector	*mc;
}	t_game;

typedef struct s_calculator
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	double	wall_x;
	double	step;
	double	texpos;

	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texnum;
	int		tex_x;
	int		tex_y;
}	t_calculator;

t_node	*create_node(char *line, t_game *game);

void	get_background_color(char *line, t_game *game, int flag);
void	input_wall_texture(int x, t_game *game, t_calculator *calc);
void	init_wall_texture(t_game *game, t_calculator *calc);
void	player_position(t_game *game, int i, int j);
void	key_leftright(t_game *game);
void	get_map_game(t_game *game);
void	deinitialize(t_game *game);
void	player_move(t_game *game);
void	perform_dda(t_game *game, t_calculator *calc);
void	placeholder(t_game *data, int x, int y);
void	parse_last(t_game *game, char *line);
void	parse_map(char *line, t_game *game);
void	check_arg(int argc, char **argv, t_game *game);
void	start_ray(int x, t_game *game, t_calculator *calc);
void	init_dda(t_game *game, t_calculator *calc);
void	add_node(t_maplist *list, t_node *node);
void	dup_map(t_game *game);
void	control(t_game *game, char **argv);

int		get_textures(char *line, t_game *game);
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
int		ft_splitlen(char **str);

#endif
