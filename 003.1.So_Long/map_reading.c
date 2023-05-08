/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:55:43 by segungor          #+#    #+#             */
/*   Updated: 2023/05/04 01:52:01 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	wall_control(t_game *data)
{
    int	i;
    int	j;
    int	width;
    int	height;

    j = 0;
    i = 0;
    width = data->map_width - 1;
    height = data->map_height - 1;
    while (i <= height)
    {
        if (data->map[i][0] != '1' || data->map[i][width] != '1')
            err_msg("the map is not covered with walls");
        i++;
    }
    while (j <= width)
    {
        if (data->map[0][j] != '1' || data->map[height][j] != '1')
            err_msg("the map is not covered with walls");
        j++;
    }
}

static void size_control(t_game *data, char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0' && line[i] != '\n')
        i++;
    if (i != data->map_width)
        err_msg("annen yamuk kalmis oc düzelteyimmi? xd:D");
}

void	map_processing(t_game *data)
{
	int		fd;
	char	*line;

	data->index.i = 0;
	data->map = (char **)malloc(sizeof(char *) * data->map_height);
	fd = open(data->maplocation, O_RDONLY);
	while (data->index.i < data->map_height)
	{
		data->index.j = 0;
		line = get_next_line(fd);
        size_control(data,line);
		data->map[data->index.i] = (char *)malloc(sizeof(char) * data->map_width);
		if (line == NULL)
			break ;
		while (data->index.j < data->map_width)
		{
			data->map[data->index.i][data->index.j] = line[data->index.j];
            data->index.j++;
		}
		data->map[data->index.i][data->index.j] = '\0';
        data->index.i++;
		free(line);
	}
	close(fd);
}

static int	width_of_map(char *string)
{
	int	width;

	width = 0;
	while (string[width] != '\n' && string[width] != '\0')
		width++;
	return (width);
}

void	map_reading(t_game *data)
{
	int		fd;
	int		x;
	int		y;
	char	*line;

	y = 0;
	fd = open(data->maplocation, O_RDONLY);
	line = get_next_line(fd);
	x = width_of_map(line);
	while (1)
	{
		free(line);
		y++;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	if (line)
		free(line);
	data->map_height = y;
	data->map_width = x;
	if (data->map_height == data->map_width
		|| data->map_width == 1 || data->map_height == 1)
		err_msg("map is not rectangular");
	close(fd);
}