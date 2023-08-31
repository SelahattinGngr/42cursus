/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printLexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:17:08 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:17:09 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdio.h"

void	print_lexer(void)
{
	t_lexlist	*lexer_temp;

	lexer_temp = g_data.lex_table;
	printf ("~LEXER TABLE~\n");
	while (lexer_temp)
	{
		printf("{type: %d, content: %s}\n", lexer_temp->type,
			lexer_temp->content);
		lexer_temp = lexer_temp->next;
	}
	printf("\n\n");
}
