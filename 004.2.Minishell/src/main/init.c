/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:18:06 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:18:07 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"
#include "unistd.h"

static void	set_metachars(void)
{
	char	**meta_list;

	meta_list = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1));
	g_data.metachars = meta_list;
	*(meta_list++) = ft_strdup(DOUBLE_GREAT);
	*(meta_list++) = ft_strdup(DOUBLE_LESS);
	*(meta_list++) = ft_strdup(SINGLE_LESS);
	*(meta_list++) = ft_strdup(SINGLE_GREAT);
	*(meta_list++) = ft_strdup(PIPE);
	*(meta_list++) = NULL;
}

void	init_core(char **env)
{
	fill_envs(env);
	set_metachars();
	set_title();
	g_data.exec_output = 0;
	g_data.old_exec_output = 0;
	g_data.main_pid = getpid();
}
