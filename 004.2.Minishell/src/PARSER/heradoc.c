/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heradoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:13:10 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:13:11 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "../../Include/myreadline.h"

static void	set_heradoc_value(t_cmdlist *node, int *fd)
{
	char	ptr[1];

	if (node->heradoc_values)
	{
		free(node->heradoc_values);
		node->heradoc_values = NULL;
	}
	while (read(fd[0], ptr, 1))
		str_addchar(&node->heradoc_values, *ptr);
	close(fd[0]);
	str_addchar(&g_data.input, '\n');
	own_strjoin(&g_data.input, node->heradoc_values);
}

static char	*get_heradoc_values(char *eof)
{
	char	*line;
	char	*newline;
	int		is_begin;

	line = NULL;
	is_begin = 0;
	while (1)
	{
		newline = readline("> ");
		if (str_compare(eof, newline))
		{
			free(newline);
			break ;
		}
		else if (is_begin++)
			str_addchar(&line, '\n');
		own_strjoin(&line, newline);
		if (newline)
			free(newline);
	}
	str_addchar(&line, '\n');
	return (line);
}

static void	fill_heradoc(char *eof, int *fd)
{
	char	*heradoc_lines;

	close(fd[0]);
	heradoc_lines = get_heradoc_values(eof);
	write(fd[1], heradoc_lines, ft_strlen(heradoc_lines));
	close(fd[1]);
	free(heradoc_lines);
	free_for_loop();
	free_core();
	exit(EXIT_SUCCESS);
}

static int	read_heradoc(t_cmdlist *node, char *eof)
{
	int		pid;
	int		fd[2];
	int		return_value;

	pipe(fd);
	pid = fork();
	g_data.is_read_arg = 1;
	if (!pid)
		fill_heradoc(eof, fd);
	close(fd[1]);
	waitpid(pid, &return_value, 0);
	g_data.is_read_arg = 0;
	return_value = WEXITSTATUS(return_value);
	if (return_value == SIGNAL_C)
	{
		close(fd[0]);
		update_history(g_data.input);
		free_for_loop();
		return (0);
	}
	set_heradoc_value(node, fd);
	return (1);
}

void	run_heradocs(t_cmdlist *node)
{
	t_filelist	*temp_file;

	while (node)
	{
		temp_file = node->files;
		while (temp_file)
		{
			if (temp_file->metachar[1] == DOUBLE_LESS[1])
			{
				if (!read_heradoc(node, temp_file->filename))
					return ;
				temp_file->fd = HERADOC;
			}
			temp_file = temp_file->next;
		}
		node = node->next;
	}
}
