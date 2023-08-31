#include "../../Include/minishell.h"

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

	data.cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	fill_cmdtable_node(data.cmd_table);
	temp_cmdtable = data.cmd_table;
	while ((--count))
	{
		temp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		fill_cmdtable_node(temp_cmdtable->next);
		temp_cmdtable = temp_cmdtable->next;
	}
}

void	create_cmdtable(t_lexlist *lex_table)
{
	int count;

	if (!lex_table)
		return ;
	count = 1;
	while (lex_table)
	{
		if (lex_table->type == SIGN_PIPE)
			count++;
		// else if (lex_table->type != TEXT)
		// {
		// 	lex_table = lex_table->next;
		// 	if (lex_table && lex_table->type == SIGN_PIPE) // sil amk
		// 		lex_table = lex_table->next;
		// 	continue ;
		// } // bu if olmasada calismaz mi awq
		lex_table = lex_table->next;
	}
	create_cmdtable_nodes(count);
}