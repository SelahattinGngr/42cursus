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

#include "../includes/utils.h"
#include "../includes/error.h"

static int	recur_func(int **int_map, t_game *data, int x, int y)
{
	if (data->map[x][y] == ' ' || data->map[x][y] == '\n' \
		|| data->map[x][y] == '\0')
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

static void	position_check(int **int_map, t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' && data->map[i][j] != '\0' \
				&& int_map[i][j] < 1)
				recur_func(int_map, data, i, j);
			j++;
		}
		i++;
	}
}

void	placeholder(t_game *data)
{
	int	**int_map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	int_map = (int **)new_malloc(data->mc, sizeof(int *) * data->map_height);
	while (i < data->map_height)
	{
		int_map[i] = (int *)new_malloc(data->mc, sizeof(int) * data->map_width);
		j = 0;
		while (j < data->map_width)
		{
			int_map[i][j] = 0;
			j++;
		}
		i++;
	}
	position_check(int_map, data);
}
