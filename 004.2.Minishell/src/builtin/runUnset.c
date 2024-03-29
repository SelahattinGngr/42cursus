/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runUnset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:14:43 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:14:44 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

void	run_unset(t_cmdlist *cmd_node)
{
	char	**temp_name;
	int		array_len;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 1)
	{
		temp_name = cmd_node->path;
		while (*(++temp_name))
		{
			if (!env_arg_control(*temp_name))
			{
				print_error("-bash: unset: `", *temp_name,
					"': not a valid identifier\n");
				g_data.exec_output = 1;
				continue ;
			}
			else
				delete_env(*temp_name);
		}
	}
}

void	delete_env(char *name)
{
	t_env	*env;
	t_env	*temp_env;

	env = g_data.env_table;
	while (env)
	{
		if (str_compare(env->env_name, name))
		{
			if (env->content)
				free(env->content);
			free(env->env_name);
			if (g_data.env_table == env)
				g_data.env_table = g_data.env_table->next;
			else
				temp_env->next = env->next;
			free(env);
			break ;
		}
		temp_env = env;
		env = env->next;
	}
}
