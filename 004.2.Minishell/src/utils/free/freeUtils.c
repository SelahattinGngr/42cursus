/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:20:22 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:20:23 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
#include "stdlib.h"

void	free_env_cpy(char **envlist)
{
	char	**temp_envlist;

	temp_envlist = envlist;
	while (*temp_envlist)
		free(*(temp_envlist++));
	free(envlist);
}

void	free_metachars(void)
{
	char	**temp_metachars;

	temp_metachars = g_data.metachars;
	if (!temp_metachars)
		return ;
	while (temp_metachars && *temp_metachars)
		free(*(temp_metachars++));
	free(g_data.metachars);
}

void	free_envtable(void)
{
	t_env	*env;
	t_env	*temp_env;

	env = g_data.env_table;
	while (env)
	{
		temp_env = env;
		env = env->next;
		free(temp_env->env_name);
		free(temp_env->content);
		free(temp_env);
	}
}

void	free_title(void)
{
	free(g_data.title.full_title);
	free(g_data.title.head);
}
