/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:17:58 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:18:01 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "../../Include/myreadline.h"

static void	free_filelist(t_filelist *files)
{
	t_filelist	*temp_files;

	while (files)
	{
		temp_files = files;
		files = files->next;
		if (temp_files->fd > SSTDERR)
			close(temp_files->fd);
		free(temp_files);
	}
}

static void	free_parser(void)
{
	t_cmdlist	*parser;
	t_cmdlist	*temp_parser;

	parser = g_data.cmd_table;
	while (parser)
	{
		temp_parser = parser;
		parser = parser->next;
		free_filelist(temp_parser->files);
		if (temp_parser->path)
			free(temp_parser->path);
		if (temp_parser->heradoc_values)
			free(temp_parser->heradoc_values);
		free(temp_parser);
	}
	g_data.cmd_table = NULL;
}

static void	free_lexer(void)
{
	t_lexlist	*lexer;
	t_lexlist	*temp_lexer;

	lexer = g_data.lex_table;
	while (lexer)
	{
		temp_lexer = lexer;
		lexer = lexer->next;
		if (temp_lexer->content)
			free(temp_lexer->content);
		free(temp_lexer);
	}
	g_data.lex_table = NULL;
}

void	free_core(void)
{
	free_metachars();
	free_envtable();
	free_title();
	rl_clear_history();
}

void	free_for_loop(void)
{
	if (g_data.input)
	{
		free(g_data.input);
		g_data.input = NULL;
	}
	if (g_data.lex_table)
		free_lexer();
	if (g_data.cmd_table)
		free_parser();
	close_heradoc_file();
}
