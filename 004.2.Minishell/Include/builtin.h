#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

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