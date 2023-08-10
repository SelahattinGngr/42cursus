/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:36:26 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:36:28 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static t_list	*group_open(t_list *l_cmd)
{
	t_list	*open;
	t_list	*iter;

	open = NULL;
	iter = l_cmd;
	while (iter != NULL)
	{
		if (cmd_content(iter)->type == CMD_O_BRACKET)
			open = iter;
		else if (open && cmd_content(iter)->type == CMD_PIPE)
			open = NULL;
		else if (open && cmd_content(iter)->type == CMD_C_BRACKET)
			return (open);
		iter = iter->next;
	}
	return (NULL);
}

static t_list	*group_close(t_list *open)
{
	t_list	*close;

	close = open;
	while (close && cmd_content(close)->type != CMD_C_BRACKET)
		close = close->next;
	if (close == open)
		return (NULL);
	return (close);
}

int	parser_cmd_group_merge(t_list **l_cmd)
{
	t_list	*group;
	t_list	*open;
	t_list	*close;

	open = group_open(*l_cmd);
	close = group_close(open);
	if (!open || !close)
		return (0);
	if (cmd_content(open->next)->type == CMD_GROUP && open->next->next == close)
	{
		lst_node_remove(l_cmd, open, c_cmd_destroy);
		lst_node_remove(l_cmd, close, c_cmd_destroy);
	}
	else
	{
		group = cmd_create(CMD_GROUP);
		if (group == NULL)
			return (ERROR);
		cmd_content(group)->l_element = open->next;
		lst_node_prev(*l_cmd, close)->next = NULL;
		lst_relink(l_cmd, group, open, close);
		ft_lstdelone(open, c_cmd_destroy);
		ft_lstdelone(close, c_cmd_destroy);
	}
	return (1);
}
