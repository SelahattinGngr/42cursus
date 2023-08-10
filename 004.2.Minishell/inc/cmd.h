/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:08:10 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:26:51 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "global.h"
# include "token.h"

# define CMD_SCMD		1
# define CMD_AND		2
# define CMD_OR			4
# define CMD_PIPE		8
# define CMD_O_BRACKET	16
# define CMD_C_BRACKET	32
# define CMD_PIPELINE	64
# define CMD_GROUP		128
# define CMD_L_SCMD		256
# define CMD_L_CMD		512

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_c_scmd;

typedef struct s_cmd_content
{
	int		type;
	t_list	*l_element;
}	t_c_cmd;

t_list		*cmd_create(int type);
t_c_cmd		*cmd_content(t_list *cmd);
void		c_cmd_destroy(void *c_cmd);
int			cmd_type(t_list *cmd);
int			cmd_type_from_token(t_list *token);
t_list		*scmd_create(int type);
t_c_scmd	*scmd_content(t_list *element);
void		c_scmd_destroy(void *c_element);

#endif
