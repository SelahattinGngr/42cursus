/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:29 by segungor          #+#    #+#             */
/*   Updated: 2024/01/18 17:34:51 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/error.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdio.h"

static void	load_image(t_game *game, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = \
	mlx_xpm_file_to_image(game->mlx, path, &img.img_width, &img.img_height);
	img.data = \
	(int *)mlx_get_data_addr(img.img, &img.bpp, &img.bpp, &img.bpp);
	y = -1;
	while (++y < img.img_height)
	{
		x = -1;
		while (++x < img.img_width)
			texture[img.img_width * y + x] = img.data[img.img_width * y + x];
	}
	mlx_destroy_image(game->mlx, img.img);
}

static void	load_texture(t_game *game, int dir, char *path)
{
	load_image(game, game->texture[dir], path);
}

static int	check_extension(char *filename, char *extension)
{
	if (!filename)
		return (EXIT_FAILURE);
	*(filename + ft_strlen(filename) - 1) = 0;
	if (ft_strncmp(filename + ft_strlen(filename) - 4, extension, 5))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	get_texture(char *line, t_game *game, int dir)
{
	int		fd;
	char	**split;

	split = ft_split(line, ' ', game);
	if (!split)
		exit_err("Malloc Error\n", game);
	if (ft_splitlen(split) != 2 || check_extension(split[1], ".xpm"))
	{
		return (RETURN_FAILURE);
	}
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
		return (RETURN_FAILURE);
	load_texture(game, dir, split[1]);
	game->dir_flag++;
	if (close(fd) < 0)
		exit_err("Close Failed Error\n", game);
	return (RETURN_SUCCESS);
}

int	get_textures(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (get_texture(line, game, NO))
			exit_err("Map: Invalid Texture Value Error\n", game);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (get_texture(line, game, EA))
			exit_err("Map: Invalid Texture Value Error\n", game);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (get_texture(line, game, SO))
			exit_err("Map: Invalid Texture Value Error\n", game);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (get_texture(line, game, WE))
			exit_err("Map: Invalid Texture Value Error\n", game);
	}
	return (RETURN_SUCCESS);
}
