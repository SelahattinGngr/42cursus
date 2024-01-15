/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:56 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:57 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "math.h"

void	init_wall_texture(t_game *game, t_calculator *calc)
{
	calc->lineheight = (int)(SCREEN_H / calc->perpwalldist);
	calc->drawstart = -calc->lineheight / 2 + SCREEN_H / 2;
	if (calc->drawstart < 0)
		calc->drawstart = 0;
	calc->drawend = calc->lineheight / 2 + SCREEN_H / 2;
	if (calc->drawend >= SCREEN_H)
		calc->drawend = SCREEN_H - 1;
	if (calc->raydir_x > 0 && calc->side == 0)
		calc->texnum = NO;
	else if (calc->raydir_x < 0 && calc->side == 0)
		calc->texnum = SO;
	else if (calc->raydir_y > 0 && calc->side == 1)
		calc->texnum = WE;
	else
		calc->texnum = EA;
	if (calc->side == 0)
		calc->wall_x = game->ray.posy + calc->perpwalldist * calc->raydir_y;
	else
		calc->wall_x = game->ray.posx + calc->perpwalldist * calc->raydir_x;
	calc->wall_x -= floor(calc->wall_x);
	calc->tex_x = (int)(calc->wall_x * (double)TEX_W);
	if (calc->side == 0 && calc->raydir_x > 0)
		calc->tex_x = TEX_W - calc->tex_x - 1;
	if (calc->side == 1 && calc->raydir_y < 0)
		calc->tex_x = TEX_W - calc->tex_x - 1;
}

void	input_wall_texture(int x, t_game *game, t_calculator *calc)
{
	int		y;
	int		color;

	calc->step = 1.0 * TEX_H / calc->lineheight;
	calc->texpos = (calc->drawstart - SCREEN_H / 2 \
		+ calc->lineheight / 2) * calc->step;
	y = -1;
	while (++y < SCREEN_H)
	{
		if (y >= calc->drawstart && y <= calc->drawend)
		{
			calc->tex_y = (int)calc->texpos & (TEX_H - 1);
			calc->texpos += calc->step;
			color = game->texture[calc->texnum] \
				[TEX_H * calc->tex_y + calc->tex_x];
			if (calc->side == 1)
				color = (color >> 1) & 8355711;
			game->buf[y][x] = color;
		}
		else if (y < calc->drawstart)
			game->buf[y][x] = game->ceiling;
		else
			game->buf[y][x] = game->floor;
	}
}
