/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:22:49 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:22:50 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
#include "stdlib.h"

void	change_title(void)
{
	char	cwd[256];

	if (g_data.title.full_title)
		free(g_data.title.full_title);
	g_data.title.full_title = NULL;
	own_strjoin(&g_data.title.full_title, g_data.title.head);
	own_strjoin(&g_data.title.full_title, (char *)getcwd(cwd, 256));
	own_strjoin(&g_data.title.full_title, "$ ");
}

void	set_title(void)
{
	g_data.title.head = NULL;
	g_data.title.full_title = NULL;
	expand_envs(&g_data.title.head, "LOGNAME");
	str_addchar(&g_data.title.head, '@');
	expand_envs(&g_data.title.head, "NAME");
	str_addchar(&g_data.title.head, ':');
	own_strjoin(&g_data.title.full_title, g_data.title.head);
}
