/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:31 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:32 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	init_map(t_game *game)
{
	int		i;

	i = -1;
	game->map = (char **)ft_calloc(game, \
		sizeof(char *) * (game->map_height + 1), 1);
	while (++i < game->map_height)
	{
		game->map[i] = \
			(char *)ft_calloc(game, sizeof(char) * (game->map_width + 1), 1);
	}
}

static t_maplist	*create_list(t_game *game)
{
	t_maplist	*list;

	list = (t_maplist *)new_malloc(game->mc, sizeof(t_maplist));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

static void	init_default(t_game *game)
{
	game->map_width = 0;
	game->map_height = 0;
	game->key_a = 0;
	game->key_w = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->color_flag = 0;
	game->dir_flag = 0;
	game->pos_flag = 0;
	game->msws = 0.035;
	game->msad = 0.035;
	game->list = create_list(game);
}

void	init_game(t_game *game)
{
	int		i;

	init_default(game);
	i = -1;
	game->buf = (int **)ft_calloc(game, sizeof(int *) * SCREEN_H, 1);
	while (++i < SCREEN_H)
	{
		game->buf[i] = (int *)ft_calloc(game, sizeof(int) * SCREEN_W, 1);
	}
	i = -1;
	game->texture = (int **)ft_calloc(game, sizeof(int *) * 4, 1);
	while (++i < 4)
	{
		game->texture[i] = \
			(int *)ft_calloc(game, sizeof(int) * (TEX_H * TEX_W), 1);
	}
}
