/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:08:26 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:27:19 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "global.h"
# include "redir.h"

# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127

int		exec_recursive(t_list *l_cmd, bool subshell, t_list *l_free);
void	exec_free_all(char **argv, t_list *l_free);
void	exec_exit_status_set(int status);
int		exec_exit_status_get(void);
int		exec_group(t_list *l_cmd, t_list *l_free);
void	exec_pipeline_pipes_init(int pipes[2][2]);
void	exec_pipeline_pipes_set(int fd[2], int pipes[2][2], int i, bool last);
void	exec_pipeline_pipes_close(int pipes[2][2], int i, bool last);
int		exec_pipeline(t_list *pipeline, t_list *l_free);
int		exec_scmd_search_path(char **argv);
int		exec_scmd(t_list *scmd, bool subshell, t_list *l_free);
int		exec_scmd_preperation(t_list *scmd, char ***argv);
int		exec_scmd_exec(char **argv);
void	exec_scmd_free_exit(int status, char **argv, t_list *l_free);
int		exec_wait_pid(int last_pid, char *name);
int		exec_wait_for_all(int last_pid);

#endif
