/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:14 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:15 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "stdlib.h"

static char	*ft_substr(char const *s, \
	unsigned int start, size_t len, t_game *game)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = (char *)new_malloc(game->mc, len + 1);
	if (!s || !(new_str))
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		count++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_strcreate(const char *s, char c, size_t i, t_game *game)
{
	size_t	len;
	size_t	tmp;

	len = 0;
	tmp = i;
	while (s[tmp] != c && s[tmp])
	{
		tmp++;
		len++;
	}
	return (ft_substr(s, i, len, game));
}

char	**ft_split(char const *s, char c, t_game *game)
{
	size_t	i;
	size_t	res_i;
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)new_malloc(game->mc, \
		(ft_count_word(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	res_i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			res[res_i++] = ft_strcreate(s, c, i, game);
		while (s[i] != c && s[i])
			i++;
	}
	res[res_i] = 0;
	return (res);
}
