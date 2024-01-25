/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:10 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 15:26:27 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "unistd.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	exit_err(char *err_msg, t_game *game)
{
	ft_putstr_fd(err_msg, 2);
	end_malloc(game->mc);
	exit(EXIT_FAILURE);
}

void	free_exit_err(char *err_msg, t_game *game)
{
	end_malloc(game->mc);
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}
