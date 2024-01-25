/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:47 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:48 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include "../includes/utils.h"

static int	check_map_content(t_game *game, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (game->pos_flag)
			return (RETURN_FAILURE);
		game->pos_flag = 1;
		return (RETURN_SUCCESS);
	}
	else if (c == ' ' || c == '0' || c == '1' || c == '\n')
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

static int	check_map(t_game *game, char *line, int size)
{
	int		i;

	i = -1;
	if (game->list->head == NULL)
	{
		while (++i < size)
		{
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
				return (RETURN_FAILURE);
		}
	}
	else
	{
		while (++i < size)
		{
			if (check_map_content(game, line[i]))
				return (RETURN_FAILURE);
		}
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1' && line[size - 1] != '1')
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

void	parse_map(char *line, t_game *game)
{
	int		size;
	t_node	*node;

	size = ft_strlen(line);
	if (check_map(game, line, size))
		exit_err("Map: Invalid Map Value\n", game);
	node = create_node(line, game);
	add_node(game->list, node);
	if (game->map_width < size)
		game->map_width = size;
	game->map_height++;
}

void	parse_last(t_game *game, char *line)
{
	t_node	*node;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(line);
	while (i < size)
	{
		if (line[i] != '1' && line[i] != ' ')
			exit_err("Map: Invalid Last Line\n", game);
		i++;
	}
	node = create_node(line, game);
	add_node(game->list, node);
	if (game->map_width < size)
		game->map_width = size;
	game->map_height++;
}
