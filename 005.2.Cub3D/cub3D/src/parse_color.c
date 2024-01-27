/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:44 by segungor          #+#    #+#             */
/*   Updated: 2024/01/18 18:01:04 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/error.h"

static int	is_valid_string(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (RETURN_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	parse_color(char *str, int *rgb, int *count, t_game *game)
{
	char	**split;
	int		i;
	int		color;

	split = ft_split(str, ',', game);
	if (!split)
		exit_err("Malloc Error\n", game);
	i = 0;
	while (split[i])
	{
		color = -1;
		if (is_valid_string(split[i]))
			return (1);
		color = ft_atoi(split[i]);
		if ((color < 0 || color > 255) || *count > 2)
			return (1);
		rgb[*count] = color;
		*count += 1;
		i++;
	}
	return (RETURN_SUCCESS);
}

static int	get_comma(char *line)
{
	int		i;
	int		comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	return (comma);
}

static void	floor_ceiling(t_game *game, int *rgb, int flag)
{
	if (flag == FLOOR)
		game->floor = ((rgb[0] * 256 * 256) + (rgb[1] * 256 + rgb[2]));
	else
		game->ceiling = ((rgb[0] * 256 * 256) + (rgb[1] * 256 + rgb[2]));
}

void	get_background_color(char *line, t_game *game, int flag)
{
	char	**split;
	int		rgb[3];
	int		i;
	int		count;

	i = 1;
	count = 0;
	if (get_comma(line) != 2)
		exit_err("Map: Invalid Color Value Error\n", game);
	split = ft_split(line, ' ', game);
	if (!split)
		exit_err("Malloc Error", game);
	if (ft_splitlen(split) < 2)
		free_exit_err("Map: Invalid Color Value Error\n", game);
	while (split[i])
	{
		if (parse_color(split[i], rgb, &count, game))
			free_exit_err("Map: Invalid Color Value Error\n", game);
		i++;
	}
	floor_ceiling(game, rgb, flag);
	game->color_flag++;
}
