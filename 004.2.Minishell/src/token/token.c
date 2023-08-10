/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:37:14 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:37:16 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/token.h"

t_list	*token_create(char *string, int type)
{
	t_c_token	*c_token;
	t_list		*token;

	c_token = malloc(sizeof(t_c_token));
	if (c_token == NULL)
		return (NULL);
	c_token->flags = type;
	c_token->str = string;
	token = ft_lstnew(c_token);
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

t_c_token	*token_content(t_list *token)
{
	return ((t_c_token *)token->content);
}

void	c_token_destroy(void *c_token)
{
	free(((t_c_token *)c_token)->str);
	((t_c_token *)c_token)->str = NULL;
	free(c_token);
}

bool	token_is_cmd(t_list *token)
{
	if (token == NULL)
		return (false);
	if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (true);
	return (false);
}

char	*token_to_str(t_list *token)
{
	char	*str;
	char	*tmp;

	if (token == NULL || token_content(token)->str == NULL)
		return (NULL);
	str = ft_strdup(token_content(token)->str);
	while (token && (token_content(token)->flags & TOK_CONNECTED))
	{
		tmp = str;
		str = ft_strjoin(str, token_content(token->next)->str);
		free(tmp);
		if (str == NULL)
			return (NULL);
		token = token->next;
	}
	return (str);
}
