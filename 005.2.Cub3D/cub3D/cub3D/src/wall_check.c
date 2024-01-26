/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:42 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 17:49:25 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

static int	control_2(char **maps, int s, int j)
{
	if ((j && s && maps[s][j - 1] == '1' && maps[s - 1][j] == '1') || \
		(j && s && maps[s][j + 1] == '0' && maps[s][j - 1] == '1' && \
		maps[s + 1][j] == '1' && maps[s - 1][j] == '0') || \
		(j && s && maps[s][j + 1] == '1' && maps[s][j - 1] == '0' && \
		maps[s + 1][j] == '0' && maps[s - 1][j] == '1') || \
		(j && maps[s][j - 1] == '1') || \
		(s && maps[s][j + 1] == '1' && maps[s - 1][j] == '1') || \
		(s && maps[s - 1][j] == '1' && maps[s + 1][j] == '1'))
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

static int	control_1(char **maps, int s, int j)
{
	if ((maps[s][j + 1] == '1' && maps[s + 1][j] == '1') || \
		(j && maps[s][j + 1] == '1' && maps[s][j - 1] == '1') || \
		(j && maps[s][j - 1] == '1' && maps[s + 1][j] == '1') || \
		(s && maps[s - 1] != NULL && maps[s - 1][j] == '1' && \
		maps[s + 1][j] == '1'))
		return (RETURN_SUCCESS);
	if ((j && s && maps[s][j + 1] == '0' && maps[s][j - 1] == '0' && \
		maps[s + 1][j] == '0' && maps[s - 1][j] == '0') || \
		(j && s && maps[s][j + 1] == '1' && maps[s][j - 1] == '0' && \
		maps[s + 1][j] == '0' && maps[s - 1][j] == '0') || \
		(j && s && maps[s][j + 1] == '0' && maps[s][j - 1] == '1' && \
		maps[s + 1][j] == '0' && maps[s - 1][j] == '0') || \
		(j && s && maps[s][j + 1] == '0' && maps[s][j - 1] == '0' && \
		maps[s + 1][j] == '1' && maps[s - 1][j] == '0') || \
		(j && s && maps[s][j + 1] == '0' && maps[s][j - 1] == '0' && \
		maps[s + 1][j] == '0' && maps[s - 1][j] == '1'))
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

static int	other_lines(char **maps, int s, int j)
{
	int	flag;

	flag = control_1(maps, s, j);
	if (flag == 1)
		flag = control_2(maps, s, j);
	return (flag);
}

void	wall_check(t_game *game)
{
	char	**maps;
	int		s;
	int		j;

	maps = game->map;
	s = -1;
	while (maps[++s])
	{
		j = 0;
		while (maps[s][j] != '\0')
		{
			if (maps[s][j] == '1')
			{
				if (maps[s + 1] != NULL)
					if (other_lines(maps, s, j))
						exit_err("Map is not closed2 Error\n", game);
			}
			j++;
		}
	}
}
