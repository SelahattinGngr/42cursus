/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:49 by segungor          #+#    #+#             */
/*   Updated: 2024/01/18 16:34:17 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include "../includes/utils.h"
#include "../get_next_line/get_next_line.h"
#include "unistd.h"
#include "fcntl.h"

static void	parse_line(t_game *game, char *line)
{
	if (game->dir_flag > 4 || game->color_flag > 2)
		exit_err(".cub: Too Much gamermation Error\n", game);
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		get_textures(line, game);
	else if (!ft_strncmp(line, "F ", 2))
		get_background_color(line, game, FLOOR);
	else if (!ft_strncmp(line, "C ", 2))
		get_background_color(line, game, CEILING);
	else if (game->list->head && ft_strlen(line) <= 1)
		exit_err(".cub: Invalid Identifier Error\n", game);
	else if (ft_strlen(line) <= 1)
		return ;
	else if (game->color_flag == 2 && game->dir_flag == 4)
		parse_map(line, game);
	else
		exit_err(".cub: Invalid Identifier Error\n", game);
}

static void	parse_cub(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(game, fd);
	while (line)
	{
		if (!line)
		{
			if (close(fd) < 0)
				exit_err("Close Failed Error\n", game);
			exit_err("GNL Error\n", game);
		}
		parse_line(game, line);
		line = get_next_line(game, fd);
	}
	if (game->dir_flag != 4 || game->color_flag != 2 || game->pos_flag != 1)
	{
		if (close(fd) < 0)
			exit_err("Close Failed Error\n", game);
		exit_err(".cub: Too Few gamermation\n", game);
	}
}

void	check_arg(int argc, char **argv, t_game *game)
{
	int		i;
	int		fd;

	if (argc != 2)
		exit_err("Input Argument Error\n", game);
	i = ft_strlen(argv[1]) - 4;
	if (ft_strncmp(&argv[1][i], ".cub", 4))
		exit_err("File Extension Error\n", game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_err(".cub Path Error\n", game);
	parse_cub(fd, game);
	if (close(fd) < 0)
		exit_err("Close Failed Error\n", game);
}
