/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:36 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:41 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/error.h"
#include "../includes/utils.h"
#include "stdlib.h"

t_node	*create_node(char *line, t_game *game)
{
	t_node	*node;

	node = (t_node *)new_malloc(game->mc, sizeof(t_node));
	node->map = ft_strdup(line, game);
	node->next = NULL;
	return (node);
}

void	add_node(t_maplist *list, t_node *node)
{
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}
