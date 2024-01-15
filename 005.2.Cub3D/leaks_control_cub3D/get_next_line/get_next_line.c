/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:37:26 by segungor          #+#    #+#             */
/*   Updated: 2023/01/05 22:37:28 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*first_line(t_game *game, int fd, char *buffer)
{
	char	*buff;
	int		rd_byte;

	rd_byte = 1;
	buff = new_malloc(game->mc, sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!find_nl_char(buffer) && rd_byte != 0)
	{
		rd_byte = read(fd, buff, BUFFER_SIZE);
		if (rd_byte == -1)
		{
			return (NULL);
		}
		buff[rd_byte] = '\0';
		buffer = strjoin(game, buffer, buff);
	}
	return (buffer);
}

char	*get_next_line(t_game *game, int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = first_line(game, fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = get_new_line(game, buffer);
	buffer = get_new_buffer(game, buffer);
	return (line);
}
