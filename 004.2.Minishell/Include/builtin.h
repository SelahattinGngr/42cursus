/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:23:17 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:23:18 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		is_builtin(char *cmd);
void	run_builtin(t_cmdlist *cmd_node, int builtin, int *fd, int fd_index);
void	run_cd(t_cmdlist *cmd_node);
void	run_unset(t_cmdlist *cmd_node);
void	delete_env(char *name);
void	run_echo(t_cmdlist *cmd_node);
void	run_env(t_cmdlist *cmd_node);
void	run_exit(t_cmdlist *cmd_node);
void	run_pwd(t_cmdlist *cmd_node);
void	run_export(t_cmdlist *cmd_node);

#endif
