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

#include "libft.h"

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

char	*get_new_line(char *buffer)
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
    line = malloc(sizeof(char) * (i + 1 + nl));
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

char	*get_new_buffer(char *buffer)
{
    char	*new_buffer;
    int		i;
    int		j;

    j = 0;
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free (buffer);
        return (NULL);
    }
    new_buffer = malloc(sizeof(char) * (ftgnl_strlen(buffer) - i + 1));
    if (!new_buffer)
        return (NULL);
    i++;
    while (buffer[i])
        new_buffer[j++] = buffer[i++];
    new_buffer[j] = 0;
    free (buffer);
    return (new_buffer);
}


char *first_line(int fd, char *buffer)
{
    char *buff;
    int rd_byte;

    rd_byte = 1;
    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return (NULL);
    while (!find_nl_char(buffer) && rd_byte != 0)
    {
        rd_byte = read(fd, buff, BUFFER_SIZE);
        if (rd_byte == -1)
        {
            free(buffer);
            free(buff);
            return (NULL);
        }
        buff[rd_byte] = '\0';
        buffer = ftgnl_strjoin(buffer, buff);
    }
    free(buff);
    return (buffer);
}

char *get_next_line(int fd)
{
    char *line;
    static char *buffer;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (0);
    buffer = first_line(fd, buffer);
    if (buffer == NULL)
        return (NULL);
    line = get_new_line(buffer);
    buffer = get_new_buffer(buffer);
    return (line);
}