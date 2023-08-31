/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:18:29 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:18:32 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "../../Include/myreadline.h"

static int	signal_while_cmd_works(void)
{
	t_cmdlist	*cmd_list;
	int			return_value;

	if (getpid() != g_data.main_pid)
		return (1);
	return_value = 0;
	cmd_list = g_data.cmd_table;
	while (cmd_list)
	{
		if (cmd_list->pid >= 0)
			return_value |= waitpid(cmd_list->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	if (return_value && getpid() == g_data.main_pid)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

static int	signal_in_reading(void)
{
	if (getpid() != g_data.main_pid && g_data.is_read_arg)
	{
		write(1, "\n", 1);
		free_for_loop();
		free_core();
		exit(SIGNAL_C);
	}
	else if (g_data.is_read_arg)
	{
		g_data.exec_output = SIGNAL_C;
		return (1);
	}
	return (0);
}

void	signalhandler(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		if (signal_in_reading())
			return ;
		if (signal_while_cmd_works())
			return ;
		g_data.exec_output = SIGNAL_C;
		write(1, "\n", 1);
		free_for_loop();
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
