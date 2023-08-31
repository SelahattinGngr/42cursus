/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearEmptyContent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:15:45 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:15:47 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

void	clear_void_contents(void)
{
	t_lexlist	*lex_list;
	t_lexlist	*temp_lex_list;

	lex_list = g_data.lex_table;
	temp_lex_list = g_data.lex_table;
	while (lex_list)
	{
		if (!lex_list->content)
		{
			if (lex_list == g_data.lex_table)
			{
				g_data.lex_table = g_data.lex_table->next;
				temp_lex_list = temp_lex_list->next;
			}
			else
				temp_lex_list->next = lex_list->next;
			free(lex_list);
			lex_list = temp_lex_list;
		}
		temp_lex_list = lex_list;
		if (lex_list)
			lex_list = lex_list->next;
	}
}
