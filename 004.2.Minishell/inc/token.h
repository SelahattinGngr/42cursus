/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:09:23 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:29:04 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "global.h"

# define TOK_TEXT			1
# define TOK_S_QUOTE		2
# define TOK_D_QUOTE		4
# define TOK_REDIR_FILE		8
# define TOK_CONNECTED		16
# define TOK_BIN_OP			32
# define TOK_PIPE			64
# define TOK_O_BRACKET		128
# define TOK_C_BRACKET		256
# define TOK_REDIR			512
# define TOK_HEREDOC		1024
# define TOK_WILDCARD		2048

typedef struct s_token_content
{
	int		flags;
	char	*str;
}	t_c_token;

t_list		*token_create(char *string, int type);
t_c_token	*token_content(t_list *token);
void		c_token_destroy(void *c_token);
bool		token_is_cmd(t_list *token);
char		*token_to_str(t_list *l_token);
char		**l_token_to_split(t_list *l_token);

#endif
