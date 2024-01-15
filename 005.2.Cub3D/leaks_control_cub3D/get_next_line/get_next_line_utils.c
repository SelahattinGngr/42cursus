/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:38:33 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:46 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *buf)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
		i++;
	return (i);
}

char	*strjoin(t_game *game, char *s1, char *s2)
{
	char	*return_str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = new_malloc(game->mc, sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	return_str = new_malloc(game->mc, sizeof(char) \
		* (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = -1;
	j = 0;
	while (s1[++i])
		return_str[i] = s1[i];
	while (s2[j])
		return_str[i++] = s2[j++];
	return_str[i] = '\0';
	return (return_str);
}

int	find_nl_char(char *buffer)
{
	int	i;

	i = -1;
	if (!buffer)
		return (0);
	while (buffer[++i])
		if (buffer[i] == '\n')
			return (1);
	return (0);
}

char	*get_new_line(t_game *game, char *buffer)
{
	char	*line;
	int		i;
	int		nl;

	nl = find_nl_char(buffer);
	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = new_malloc(game->mc, sizeof(char) * (i + 1 + nl));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*get_new_buffer(t_game *game, char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (NULL);
	new_buffer = new_malloc(game->mc, sizeof(char) \
		* (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = 0;
	return (new_buffer);
}
