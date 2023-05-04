/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:03:51 by segungor          #+#    #+#             */
/*   Updated: 2023/05/04 00:43:50 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	right_move(t_game *data, int i, int j)
{
	if (data->map[j][i] == 'E')
	{
		if (data->collectables != 0)
			return (0);
		ft_printf("\nWIN AMIGO\n");
		exit_point(data);
	}
	if (data->map[j][i] == '0')
	{
		data->map[j][i] = 'P';
		data->x_axis = i;
		data->y_axis = j;
		data->counter++;
	}
	if (data->map[j][i] == 'C')
	{
		data->map[j][i] = 'P';
		data->x_axis = i;
		data->y_axis = j;
		data->collectables--;
		data->counter++;
	}
	return (1);
}

static int	keyboard_w_s(t_game *data, int movement)
{
	data->index.i = data->x_axis;
	data->index.j = data->y_axis;
	if (movement == 13 || movement == 126)
	{
		if (data->map[--data->index.j][data->index.i] == '1')
			return (0);
		data->index.k = right_move(data, data->index.i, data->index.j);
		if (!data->index.k)
			return (0);
		data->map[data->index.j + 1][data->index.i] = '0';
	}
	else if (movement == 1 || movement == 125)
	{
		if (data->map[++data->index.j][data->index.i] == '1')
			return (0);
		data->index.k = right_move(data, data->index.i, data->index.j);
		if (!data->index.k)
			return (0);
		data->map[data->index.j - 1][data->index.i] = '0';
	}
	ft_printf("Step Count: %d\n", data->counter);
	ft_printf("Remaining Coins: %d\n", data->collectables);
	return (1);
}

static int	keyboard_a_d(t_game *data, int movement)
{
	data->index.i = data->x_axis;
	data->index.j = data->y_axis;
	if (movement == 0 || movement == 123)
	{
		if (data->map[data->index.j][--data->index.i] == '1')
			return (0);
		data->index.k = right_move(data, data->index.i, data->index.j);
		if (!data->index.k)
			return (0);
		data->map[data->index.j][data->index.i + 1] = '0';
	}
	else if (movement == 2 || movement == 124)
	{
		if (data->map[data->index.j][++data->index.i] == '1')
			return (0);
		data->index.k = right_move(data, data->index.i, data->index.j);
		if (!data->index.k)
			return (0);
		data->map[data->index.j][data->index.i - 1] = '0';
	}
	ft_printf("Step Count: %d\n", data->counter);
	ft_printf("Remaining Coins: %d\n", data->collectables);
	return (1);
}

int	controls_working(int command, t_game *data)
{
	int	works;

	if (command == 53)
		exit_point(data);
	if (command == 13 || command == 126)
		works = keyboard_w_s(data, command);
	if (command == 1 || command == 125)
		works = keyboard_w_s(data, command);
	if (command == 0 || command == 123)
		works = keyboard_a_d(data, command);
	if (command == 2 || command == 124)
		works = keyboard_a_d(data, command);
	if (works)
		adding_in_graphics(data);
	return (1);
}
