/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdtable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:12:42 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:12:43 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

static void	fill_cmdtable_node(t_cmdlist *node)
{
	node->pid = -1;
	node->infile = SSTDIN;
	node->outfile = SSTDOUT;
	node->cmd = NULL;
	node->path = NULL;
	node->next = NULL;
	node->files = NULL;
	node->heradoc_values = NULL;
}

static void	create_cmdtable_nodes(int count)
{
	t_cmdlist	*temp_cmdtable;

	g_data.cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	fill_cmdtable_node(g_data.cmd_table);
	temp_cmdtable = g_data.cmd_table;
	while ((--count))
	{
		temp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		fill_cmdtable_node(temp_cmdtable->next);
		temp_cmdtable = temp_cmdtable->next;
	}
}

void	create_cmdtable(t_lexlist *lex_table)
{
	int	count;

	if (!lex_table)
		return ;
	count = 1;
	while (lex_table)
	{
		if (lex_table->type == SIGN_PIPE)
			count++;
		lex_table = lex_table->next;
	}
	create_cmdtable_nodes(count);
}
