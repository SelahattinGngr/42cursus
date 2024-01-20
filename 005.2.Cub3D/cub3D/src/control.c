/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:49 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 17:48:14 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/error.h"
#include "../includes/utils.h"
#include "../get_next_line/get_next_line.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdio.h"

static int	direction_repeat_control(t_game *game, int fd)
{
	char	*line;
	int		no;
	int		we;
	int		ea;
	int		so;

	no = 0;
	we = 0;
	ea = 0;
	so = 0;
	line = get_next_line(game, fd);
	while (line)
	{
		if (!ft_strncmp(line, "NO ", 3))
			no++;
		else if (!ft_strncmp(line, "SO ", 3))
			so++;
		else if (!ft_strncmp(line, "EA ", 3))
			ea++;
		else if (!ft_strncmp(line, "WE ", 3))
			we++;
		delete_malloc(game->mc, line);
		line = get_next_line(game, fd);
	}
	return ((no == 0 || we == 0 || ea == 0 || so == 0));
}

static int	rgb_control(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ',' && !ft_isdigit(line[i - 1]))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	c_f_control(t_game *game, char *file)
{
	char	*line;
	int		fd;
	int		c;
	int		f;

	fd = open(file, O_RDONLY);
	c = 0;
	f = 0;
	line = get_next_line(game, fd);
	while (line)
	{
		if (!ft_strncmp(line, "C ", 2))
			c = rgb_control(line);
		else if (!ft_strncmp(line, "F ", 2))
			f = rgb_control(line);
		delete_malloc(game->mc, line);
		line = get_next_line(game, fd);
	}
	close(fd);
	return (c != 0 || f != 0);
}

void	control(t_game *game, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (direction_repeat_control(game, fd))
		exit_err("direction repeat error.\n", game);
	close(fd);
	if (c_f_control(game, argv[1]))
		exit_err("C/F error.\n", game);
}
