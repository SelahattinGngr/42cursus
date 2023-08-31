#include "../../Include/minishell.h"


static int	is_all_numeric(char *text)
{
	while (text && *text)
	{
		if (!(*text >= '0' && *text <= '9'))
			return (0);
		text++;
	}
	return (1);
}

void	run_exit(t_cmdlist *cmd_node)
{
	int	array_len;

	array_len = get_array_len(&cmd_node->path[1]);
	if (array_len > 1)
	{
		print_error("bash: exit: too many arguments\n", NULL, NULL);
		data.exec_output = 1;
		return ;
	}
	else if (array_len == 1)
	{
		if (is_all_numeric(cmd_node->path[1]))
			data.exec_output = ft_atoi(cmd_node->path[1]);
		else
		{
			print_error("bash: exit: ",
				cmd_node->path[1], ": numeric argument required\n");
			data.exec_output = 255;
		}
	}
	else
		data.exec_output = 0;
	free_for_loop();
	free_core();
	exit(data.exec_output % 256);
}