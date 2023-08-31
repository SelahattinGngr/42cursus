#include "../../Include/minishell.h"


static void	update_exec_output(void)
{
	data.old_exec_output = data.old_exec_output ^ data.exec_output;
	data.exec_output = data.old_exec_output ^ data.exec_output;
	data.old_exec_output = data.old_exec_output ^ data.exec_output;
	data.exec_output = 0;
}

void	update_loop(void)
{
	update_exec_output();
	data.is_read_arg = 0;
}

void	update_history(char *cmd)
{
	char	*ptr;

	if (!cmd)
		return ;
	ptr = cmd;
	trim_spaces(&ptr);
	if (!*ptr)
		return ;
	add_history(cmd);
}