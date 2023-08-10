/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:30:39 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:30:40 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include "../inc/cmd.h"

int	exec_group(t_list *l_cmd, t_list *l_free)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (print_error_errno(SHELL_NAME, NULL, NULL));
	if (pid == 0)
	{
		status = exec_recursive(cmd_content(l_cmd)->l_element, true, l_free);
		exec_free_all(NULL, l_free);
		exit(status);
	}
	return (exec_wait_pid(pid, NULL));
}
