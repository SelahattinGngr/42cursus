/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:26 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 18:46:51 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/utils.h"
#include "../includes/error.h"

static void	b_space(t_game *game, t_node *node, int i)
{
	int		j;

	j = ft_strlen(node->map);
	while (j < game->map_width)
	{
		game->map[i][j] = ' ';
		j++;
	}
	game->map[i][game->map_width] = '\0';
}

void	dup_map(t_game *game)
{
	int		i;
	t_node	*node;
	t_node	*temp;

	node = game->list->head;
	i = 0;
	while (node)
	{
		ft_strlcpy(game->map[i], node->map, ft_strlen(node->map) + 1);
		if (ft_strlen(node->map) < (size_t)game->map_width)
			b_space(game, node, i);
		temp = node;
		node = node->next;
		game->list->size--;
		i++;
	}
	game->map[i] = NULL;
}

static int	check_blank(t_game *game, int i, int j)
{
	if (i - 1 > 0)
		if (game->map[i - 1][j] != ' ' \
			&& game->map[i - 1][j] != '1' && game->map[i - 1][j] != '\n')
			return (RETURN_FAILURE);
	if (j - 1 > 0)
		if (game->map[i][j - 1] != ' ' \
			&& game->map[i][j - 1] != '1' && game->map[i][j - 1] != '\n')
			return (RETURN_FAILURE);
	if (i + 1 < game->map_height)
		if (game->map[i + 1][j] != ' ' \
			&& game->map[i + 1][j] != '1' && game->map[i + 1][j] != '\n')
			return (RETURN_FAILURE);
	if (j + 1 < game->map_width)
		if (game->map[i][j + 1] != ' ' \
			&& game->map[i][j + 1] != '1' && game->map[i][j + 1] != '\n')
			return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

void	get_map_game(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (ft_isalpha(game->map[i][j]))
			{
				player_position(game, i, j);
				x = i;
				y = j;
			}
			else if (game->map[i][j] == ' ')
				if (check_blank(game, i, j))
					exit_err("Invalid map\n", game);
		}
	}
	placeholder(game);
}
