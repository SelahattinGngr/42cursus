/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:31:55 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:31:56 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

int	lexer_token_bin_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if ((str[*i] == '&' && str[*i + 1] == '&')
		|| (str[*i] == '|' && str[*i + 1] == '|'))
	{
		token_str = ft_substr(str, *i, 2);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_BIN_OP);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += 2;
	}
	return (0);
}

int	lexer_token_redir(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = 0;
	while (ft_isdigit(str[*i + len]))
		len++;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_REDIR);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += len;
	}
	return (0);
}

int	lexer_token_pipe(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '|')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_PIPE);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
	return (0);
}

int	lexer_token_bracket(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '(' || str[*i] == ')')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '(')
			token = token_create(token_str, TOK_O_BRACKET);
		else
			token = token_create(token_str, TOK_C_BRACKET);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
	return (0);
}
