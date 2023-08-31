#include "../../Include/minishell.h"

void	run_env(t_cmdlist *cmd_node)
{
	t_env	*temp_env;

	temp_env = data.env_table;
	while (temp_env)
	{
		if (temp_env->content)
		{
			write(cmd_node->outfile, temp_env->env_name,
				ft_strlen(temp_env->env_name));
			write(cmd_node->outfile, "=", 1);
			write(cmd_node->outfile, temp_env->content,
				ft_strlen(temp_env->content));
			write(cmd_node->outfile, "\n", 1);
		}
		temp_env = temp_env->next;
	}
}
