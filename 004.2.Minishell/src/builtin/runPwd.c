/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runPwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:14:34 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:14:36 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "unistd.h"

void	run_pwd(t_cmdlist *cmd_node)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(cmd_node->outfile, pwd, ft_strlen(pwd));
	write(cmd_node->outfile, "\n", 1);
}
