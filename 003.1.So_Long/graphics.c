/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 02:17:51 by segungor          #+#    #+#             */
/*   Updated: 2023/05/04 02:23:11 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_player(t_game *data, int height, int width)
{
	mlx_put_image_to_window(data->mlxpointer,
		data->winpointer, data->player, width * 40, height * 40);
	data->y_axis = height;
	data->x_axis = width;
}

void	place_collectable(t_game *data, int height, int width)
{
	mlx_put_image_to_window(data->mlxpointer,
		data->winpointer, data->collectable, width * 40, height * 40);
	data->collectables++;
}

void	images_in_game(t_game *data)
{
	int	i;
	int	j;

	data->floor = mlx_xpm_file_to_image(data->mlxpointer,
			"images/floor.xpm", &i, &j);
	data->barrier = mlx_xpm_file_to_image(data->mlxpointer,
			"images/wall.xpm", &i, &j);
	data->player = mlx_xpm_file_to_image(data->mlxpointer,
			"images/player.xpm", &i, &j);
	data->exit = mlx_xpm_file_to_image(data->mlxpointer,
			"images/exit.xpm", &i, &j);
	data->collectable = mlx_xpm_file_to_image(data->mlxpointer,
			"images/item.xpm", &i, &j);
}

void	adding_in_graphics(t_game *data)
{
	int	height;
	int	width;

	data->collectables = 0;
	height = -1;
	while (++height < data->map_height)
	{
		width = -1;
		while (data->map[height][++width])
		{
			if (data->map[height][width] == '1')
				mlx_put_image_to_window(data->mlxpointer,
					data->winpointer, data->barrier, width * 40, height * 40);
			if (data->map[height][width] == 'C')
				place_collectable(data, height, width);
			if (data->map[height][width] == 'P')
				place_player(data, height, width);
			if (data->map[height][width] == 'E')
				mlx_put_image_to_window(data->mlxpointer,
					data->winpointer, data->exit, width * 40, height * 40);
			if (data->map[height][width] == '0')
				mlx_put_image_to_window(data->mlxpointer,
					data->winpointer, data->floor, width * 40, height * 40);
		}
	}
}
