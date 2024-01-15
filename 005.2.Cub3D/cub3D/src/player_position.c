/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:52 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:53 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_position(t_game *game, int i, int j)
{
	game->ray.posx = i + 0.5;
	game->ray.posy = j + 0.5;
	if (game->map[i][j] == 'E')
	{
		game->ray.diry = 1;
		game->ray.planex = 0.66;
	}
	else if (game->map[i][j] == 'W')
	{
		game->ray.diry = -1;
		game->ray.planex = -0.66;
	}
	else if (game->map[i][j] == 'S')
	{
		game->ray.dirx = 1;
		game->ray.planey = -0.66;
	}
	else if (game->map[i][j] == 'N')
	{
		game->ray.dirx = -1;
		game->ray.planey = 0.66;
	}
}
