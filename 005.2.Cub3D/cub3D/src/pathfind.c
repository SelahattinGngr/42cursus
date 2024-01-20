/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:42 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 18:48:15 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/utils.h"
#include "../includes/error.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

static int	recur_func(int **int_map, t_game *data, int x, int y)
{
	if (data->map[x][y] == ' ' || data->map[x][y] == '\n')
		exit_err("path find error.\n", data);
	if (data->map[x][y + 1] != '1' && int_map[x][y + 1] < 1)
	{
		int_map[x][y + 1] = int_map[x][y] + 1;
		recur_func(int_map, data, x, y + 1);
	}
	if (data->map[x + 1][y] != '1' && int_map[x + 1][y] < 1)
	{
		int_map[x + 1][y] = int_map[x][y] + 1;
		recur_func(int_map, data, x + 1, y);
	}
	if (data->map[x][y - 1] != '1' && int_map[x][y - 1] < 1)
	{
		int_map[x][y - 1] = int_map[x][y] + 1;
		recur_func(int_map, data, x, y - 1);
	}
	if (data->map[x - 1][y] != '1' && int_map[x - 1][y] < 1)
	{
		int_map[x - 1][y] = int_map[x][y] + 1;
		recur_func(int_map, data, x - 1, y);
	}
	return (RETURN_SUCCESS);
}

void	placeholder(t_game *data, int x, int y)
{
	int	**int_map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	int_map = (int **)malloc(sizeof(int *) * data->map_height);
	while (i < data->map_height)
	{
		int_map[i] = (int *)malloc(sizeof(int) * data->map_width);
		j = 0;
		while (j < data->map_width)
		{
			int_map[i][j] = 0;
			j++;
		}
		i++;
	}
	int_map[x][y] = 1;
	if (recur_func(int_map, data, x, y))
		exit_err("path find error.\n", data);
}
