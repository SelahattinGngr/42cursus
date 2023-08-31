/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runEnv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:14:10 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:14:11 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "unistd.h"

void	run_env(t_cmdlist *cmd_node)
{
	t_env	*temp_env;

	temp_env = g_data.env_table;
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
