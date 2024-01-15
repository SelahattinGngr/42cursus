/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:36:01 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:02 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "stdlib.h"

void	key_leftright(t_game *game)
{
	if (game->key_a)
	{
		if (game->map[(int)(game->ray.posx - 1 \
			* game->ray.diry * game->msad * 15)] \
			[(int)(game->ray.posy)] != '1')
			game->ray.posx = game->ray.posx - 1 * game->ray.diry * game->msad;
		if (game->map[(int)(game->ray.posx)] \
			[(int)(game->ray.posy + 1 \
			* game->ray.dirx * game->msad * 15)] != '1')
			game->ray.posy = game->ray.posy + 1 * game->ray.dirx * game->msad;
	}
	if (game->key_d)
	{
		if (game->map[(int)(game->ray.posx + 1 \
		* game->ray.diry * game->msad * 15)] \
			[(int)(game->ray.posy)] != '1')
			game->ray.posx = game->ray.posx + 1 * game->ray.diry * game->msad;
		if (game->map[(int)(game->ray.posx)] \
			[(int)(game->ray.posy - 1 \
			* game->ray.dirx * game->msad * 15)] != '1')
			game->ray.posy = game->ray.posy - 1 * game->ray.dirx * game->msad;
	}
}

void	deinitialize(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
}
