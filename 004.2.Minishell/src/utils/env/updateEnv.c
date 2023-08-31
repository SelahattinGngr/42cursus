/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateEnv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:19:22 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:19:24 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
#include "stdlib.h"

int	update_env(char *env_name, char *new_arg)
{
	t_env	*env;

	env = g_data.env_table;
	while (env)
	{
		if (str_compare(env->env_name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			own_strjoin(&env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
