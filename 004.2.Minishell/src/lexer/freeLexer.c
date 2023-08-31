/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeLexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:16:44 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:16:45 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

static int	skip_heradoc(t_lexlist **lex,
		t_lexlist **temp, t_lexlist *stop, int *flag)
{
	if (stop == *lex)
		*flag |= 1;
	if ((*lex)->type == SIGN_DOUBLE_LESS && !*flag)
	{
		if ((*lex) && (*lex) != stop)
			*lex = (*lex)->next;
		*temp = *lex;
		*lex = (*lex)->next;
		return (1);
	}
	return (0);
}

void	free_lexer_without_heradoc(t_lexlist *stop_list)
{
	t_lexlist	*lexer;
	t_lexlist	*temp_lexer;
	int			flag;

	lexer = g_data.lex_table;
	flag = 0;
	while (lexer)
	{
		if (skip_heradoc(&lexer, &temp_lexer, stop_list, &flag))
			continue ;
		if (g_data.lex_table == lexer)
		{
			g_data.lex_table = g_data.lex_table->next;
			temp_lexer = g_data.lex_table;
		}
		else
			temp_lexer->next = lexer->next;
		free(lexer->content);
		free(lexer);
		if (g_data.lex_table == temp_lexer)
			lexer = temp_lexer;
		else
			lexer = temp_lexer->next;
	}
}
