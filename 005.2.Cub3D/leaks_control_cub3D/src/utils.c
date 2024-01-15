/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:02 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:59 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "stdlib.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_splitlen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pdst;

	i = 0;
	pdst = (unsigned char *)s;
	while (i < n)
	{
		pdst[i] = c;
		i++;
	}
	return (pdst);
}

void	*ft_calloc(t_game *game, size_t count, size_t size)
{
	size_t	tot_size;
	void	*dst;

	tot_size = size * count;
	dst = new_malloc(game->mc, tot_size);
	ft_memset(dst, 0, tot_size);
	return (dst);
}
