/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:21 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:22 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "stdlib.h"
#include "unistd.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((dest == src) || n == 0)
		return (dest);
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s1, t_game *game)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s1);
	dest = (char *)new_malloc(game->mc, len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_free(char *s1, char *s2, t_game *game)
{
	size_t		len_s1;
	size_t		len_s2;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2, game));
	else if (!s2)
		return (ft_strdup(s1, game));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)new_malloc(game->mc, sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = 0;
	return (str);
}
