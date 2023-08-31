/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runProcess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:15:21 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:15:22 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

void	run_process(t_cmdlist *cmd_list, int *fd, int fd_index)
{
	if (cmd_list->infile != SSTDERR && cmd_list->outfile != SSTDERR)
		exec_command(cmd_list, fd, fd_index);
	else
		clear_pipe(fd);
	free_for_loop();
	free_core();
	exit(g_data.exec_output);
}

void	wait_all(void)
{
	t_cmdlist	*cmd_list;

	cmd_list = g_data.cmd_table;
	while (cmd_list)
	{
		if (!cmd_list->next)
			waitpid(cmd_list->pid, &g_data.exec_output, 0);
		else
			waitpid(cmd_list->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	g_data.exec_output = WEXITSTATUS(g_data.exec_output);
}
