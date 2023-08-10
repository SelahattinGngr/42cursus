/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:09:13 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:28:43 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "global.h"
# include "token.h"

# define REDIR_OUT		1
# define REDIR_OUT_APP	2
# define REDIR_IN		3
# define REDIR_HEREDOC	4

# define REDIR_FILE		0
# define REDIR_NUM		1

typedef struct s_redir_undo_content
{
	int		fd_repl;
	int		fd_repl_dup;
}	t_c_redir_undo;

int	redir(t_list *l_token, t_list **l_undo);
int	redir_type(char *redir);
int	redir_undo(t_list **l_undo);
int	redir_undo_add_fd(t_list **l_undo, int fd);

#endif
