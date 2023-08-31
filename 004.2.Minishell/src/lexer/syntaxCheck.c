/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxCheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:17:18 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:17:19 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

static int	run_miss_arg(t_lexlist *lex_list)
{
	char	*ptr;

	ptr = get_missing_arg();
	if (!ptr)
		return (1);
	create_lexlist(ptr, &lex_list);
	classify(lex_list);
	str_addchar(&g_data.input, ' ');
	own_strjoin(&g_data.input, ptr);
	free(ptr);
	if (str_compare(lex_list->next->content, PIPE))
		return (-1);
	return (1);
}

static int	pipe_error_check(t_lexlist *lex_list)
{
	if (lex_list->next && lex_list->next->type == SIGN_PIPE)
		return (print_lex_error(lex_list));
	else if (!lex_list->next)
		return (run_miss_arg(lex_list));
	return (1);
}

static int	file_error_check(t_lexlist *lex_list)
{
	if (!lex_list->next || (lex_list->next && lex_list->next->type != TEXT))
	{
		if (lex_list->next)
		{
			print_error("-bash: syntax error near unexpected token '",
				lex_list->next->content, "'\n");
			g_data.exec_output = 2;
			free_lexer_without_heradoc(lex_list);
			return (0);
		}
		else
		{
			print_error("-bash: syntax error near unexpected token '",
				"newline", "'\n");
			g_data.exec_output = 2;
			free_lexer_without_heradoc(lex_list);
			return (0);
		}
	}
	return (1);
}

static int	syntax_error_check(t_lexlist *lex_list)
{
	int	pipe_error;

	if (lex_list == g_data.lex_table && lex_list->type == SIGN_PIPE)
	{
		print_lex_error(lex_list);
		return (-1);
	}
	else if (lex_list->type != TEXT && lex_list->type != SIGN_PIPE)
	{
		if (!file_error_check(lex_list))
			return (-1);
	}
	else if (lex_list->type == SIGN_PIPE)
	{
		pipe_error = pipe_error_check(lex_list);
		if (pipe_error < 0)
			return (0);
		else if (!pipe_error)
			return (-1);
	}
	return (1);
}

void	syntax_check(void)
{
	t_lexlist	*lex_list;
	int			syntax_error;

	lex_list = g_data.lex_table;
	while (lex_list)
	{
		syntax_error = syntax_error_check(lex_list);
		if (syntax_error == -1)
			break ;
		else if (!syntax_error)
			continue ;
		if (g_data.lex_table)
			lex_list = lex_list->next;
		else
			lex_list = NULL;
	}
}
