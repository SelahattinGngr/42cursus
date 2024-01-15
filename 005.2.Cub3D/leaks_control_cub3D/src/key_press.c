/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:34 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:35 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "math.h"
#include "stdlib.h"

static void	close_window(t_game *game)
{
	deinitialize(game);
	end_malloc(game->mc);
	exit(EXIT_SUCCESS);
}

static void	rotate_vector(t_game *game, double angle)
{
	double	oldirx;
	double	oldplanex;

	oldirx = game->ray.dirx;
	oldplanex = game->ray.planex;
	game->ray.dirx = game->ray.dirx * cos(angle) - game->ray.diry * sin(angle);
	game->ray.diry = oldirx * sin(angle) + game->ray.diry * cos(angle);
	game->ray.planex = \
		game->ray.planex * cos(angle) - game->ray.planey * sin(angle);
	game->ray.planey = \
		oldplanex * sin(angle) + game->ray.planey * cos(angle);
}

void	player_move(t_game *game)
{
	if (game->key_w)
	{
		if (game->map[(int)(game->ray.posx + game->ray.dirx * game->msws * 15)] \
			[(int)(game->ray.posy)] != '1')
			game->ray.posx += game->ray.dirx * game->msws;
		if (game->map[(int)(game->ray.posx)] \
			[(int)(game->ray.posy + game->ray.diry * game->msws * 15)] != '1')
			game->ray.posy += game->ray.diry * game->msws;
	}
	if (game->key_s)
	{
		if (game->map[(int)(game->ray.posx - game->ray.dirx * game->msws * 15)] \
			[(int)(game->ray.posy)] != '1')
			game->ray.posx -= game->ray.dirx * game->msws;
		if (game->map[(int)(game->ray.posx)] \
			[(int)(game->ray.posy - game->ray.diry * game->msws * 15)] != '1')
			game->ray.posy -= game->ray.diry * game->msws;
	}
	if (game->key_a || game->key_d)
		key_leftright(game);
	if (game->key_right)
		rotate_vector(game, -0.05);
	if (game->key_left)
		rotate_vector(game, 0.05);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->key_w = 1;
	else if (keycode == KEY_A)
		game->key_a = 1;
	else if (keycode == KEY_S)
		game->key_s = 1;
	else if (keycode == KEY_D)
		game->key_d = 1;
	else if (keycode == KEY_LEFT)
		game->key_left = 1;
	else if (keycode == KEY_RIGHT)
		game->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->key_w = 0;
	else if (keycode == KEY_A)
		game->key_a = 0;
	else if (keycode == KEY_S)
		game->key_s = 0;
	else if (keycode == KEY_D)
		game->key_d = 0;
	else if (keycode == KEY_LEFT)
		game->key_left = 0;
	else if (keycode == KEY_RIGHT)
		game->key_right = 0;
	return (0);
}
