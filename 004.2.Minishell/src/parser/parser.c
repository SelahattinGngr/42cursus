/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:36:46 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:36:48 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/env.h"

static int	parser_recursive_merge(t_list **l_cmd)
{
	int	group;
	int	pipeline;

	group = 1;
	pipeline = 1;
	while (group > 0 || pipeline > 0)
	{
		group = parser_cmd_group_merge(l_cmd);
		if (group == ERROR)
			return (ERROR);
		pipeline = parser_cmd_pipeline_merge(l_cmd);
		if (pipeline == ERROR)
			return (ERROR);
	}
	return (0);
}

t_list	*parser(t_list *l_token)
{
	t_list	*l_cmd;

	l_cmd = parser_scmd_tokens(l_token);
	if (l_cmd == NULL)
		return (NULL);
	if (parser_recursive_merge(&l_cmd) == ERROR)
	{
		ft_lstclear(&l_cmd, c_cmd_destroy);
		return (NULL);
	}
	return (l_cmd);
}
