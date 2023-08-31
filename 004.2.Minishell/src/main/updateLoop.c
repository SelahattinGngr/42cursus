/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateLoop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:18:38 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:18:41 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "../../Include/myreadline.h"

static void	update_exec_output(void)
{
	g_data.old_exec_output = g_data.old_exec_output ^ g_data.exec_output;
	g_data.exec_output = g_data.old_exec_output ^ g_data.exec_output;
	g_data.old_exec_output = g_data.old_exec_output ^ g_data.exec_output;
	g_data.exec_output = 0;
}

void	update_loop(void)
{
	update_exec_output();
	g_data.is_read_arg = 0;
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
