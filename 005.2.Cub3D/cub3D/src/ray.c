/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:54 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:55 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "math.h"

void	init_dda(t_game *game, t_calculator *calc)
{
	if (calc->raydir_x < 0)
	{
		calc->step_x = -1;
		calc->sidedist_x = (game->ray.posx - calc->map_x) * calc->deltadist_x;
	}
	else
	{
		calc->step_x = 1;
		calc->sidedist_x = \
			(calc->map_x + 1.0 - game->ray.posx) * calc->deltadist_x;
	}
	if (calc->raydir_y < 0)
	{
		calc->step_y = -1;
		calc->sidedist_y = \
			(game->ray.posy - calc->map_y) * calc->deltadist_y;
	}
	else
	{
		calc->step_y = 1;
		calc->sidedist_y = \
		(calc->map_y + 1.0 - game->ray.posy) * calc->deltadist_y;
	}
}

void	perform_dda(t_game *game, t_calculator *calc)
{
	while (calc->hit == 0)
	{
		if (calc->sidedist_x < calc->sidedist_y)
		{
			calc->sidedist_x += calc->deltadist_x;
			calc->map_x += calc->step_x;
			calc->side = 0;
		}
		else
		{
			calc->sidedist_y += calc->deltadist_y;
			calc->map_y += calc->step_y;
			calc->side = 1;
		}
		if (game->map[calc->map_x][calc->map_y] == '1')
			calc->hit = 1;
	}
	if (calc->side == 0)
		calc->perpwalldist = (calc->map_x - game->ray.posx + \
			(1 - calc->step_x) / 2) / calc->raydir_x;
	else
		calc->perpwalldist = (calc->map_y - game->ray.posy + \
			(1 - calc->step_y) / 2) / calc->raydir_y;
}

void	start_ray(int x, t_game *game, t_calculator *calc)
{
	calc->camera_x = (2 * x / (double)SCREEN_W) - 1;
	calc->raydir_x = game->ray.dirx + game->ray.planex * calc->camera_x;
	calc->raydir_y = game->ray.diry + game->ray.planey * calc->camera_x;
	calc->map_x = (int)game->ray.posx;
	calc->map_y = (int)game->ray.posy;
	calc->deltadist_x = \
	sqrt(1 + (calc->raydir_y * calc->raydir_y) \
		/ (calc->raydir_x * calc->raydir_x));
	calc->deltadist_y = \
	sqrt(1 + (calc->raydir_x * calc->raydir_x) \
		/ (calc->raydir_y * calc->raydir_y));
	calc->hit = 0;
}
