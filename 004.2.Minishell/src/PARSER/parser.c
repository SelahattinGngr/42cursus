#include "../../Include/minishell.h"

void	parser(void)
{
	data.cmd_table = NULL;
	create_cmdtable(data.lex_table);
	fill_cmdTable();
	create_files(data.cmd_table);
}
