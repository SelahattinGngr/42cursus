/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execCmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:15:03 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:15:04 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"
#include "unistd.h"

static int	get_env_len(void)
{
	t_env	*env_list;
	int		count;

	env_list = g_data.env_table;
	count = 0;
	while (env_list)
	{
		if (env_list->content)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	**get_env_cpy(void)
{
	int		env_len;
	char	**envlist;
	char	*temp_env;
	t_env	*temp_envlist;

	env_len = get_env_len();
	envlist = (char **)malloc(sizeof(char *) * (env_len + 1));
	envlist[env_len] = NULL;
	temp_envlist = g_data.env_table;
	while (temp_envlist)
	{
		if (temp_envlist->content)
		{
			temp_env = NULL;
			own_strjoin(&temp_env, temp_envlist->env_name);
			str_addchar(&temp_env, '=');
			own_strjoin(&temp_env, temp_envlist->content);
			envlist[--env_len] = temp_env;
		}
		temp_envlist = temp_envlist->next;
	}
	return (envlist);
}

static void	run_execve(t_cmdlist *cmd_node, int *fd, int fd_index)
{
	char	**envlist;

	cmd_node->pid = fork();
	if (!cmd_node->pid)
	{
		create_dup(cmd_node, fd, fd_index);
		envlist = get_env_cpy();
		if (execve(cmd_node->cmd, cmd_node->path, envlist) == -1)
		{
			if (cmd_node->cmd)
				print_error(cmd_node->cmd, " command not found\n", NULL);
			free_env_cpy(envlist);
			free_for_loop();
			free_core();
			exit(127);
		}
	}
	if (fd && cmd_node->pid)
		clear_pipe(fd);
	waitpid(cmd_node->pid, &g_data.exec_output, 0);
	g_data.exec_output = WEXITSTATUS(g_data.exec_output);
}

static char	*get_cmd(char *cmd)
{
	int		command_len;

	command_len = 0;
	while (*cmd)
	{
		command_len++;
		if (*cmd == '/')
			command_len = 0;
		cmd++;
	}
	return (cmd - command_len);
}

void	exec_command(t_cmdlist *cmd_node, int *fd, int fd_index)
{
	char	*cmd;
	int		builtin_index;

	if (cmd_node && !cmd_node->cmd)
		return ;
	cmd = get_cmd(cmd_node->cmd);
	builtin_index = is_builtin(cmd);
	if (builtin_index)
		run_builtin(cmd_node, builtin_index, fd, fd_index);
	else
		run_execve(cmd_node, fd, fd_index);
}
