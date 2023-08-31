/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CompareMeta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:20:36 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:20:37 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
#include "stdlib.h"

char	*compare_metachars(char *cmd_line)
{
	char	**meta_chars;

	if (!cmd_line)
		return (NULL);
	meta_chars = g_data.metachars;
	while (meta_chars && *meta_chars)
	{
		if ((*cmd_line == **meta_chars && !*(*meta_chars + 1))
			|| (*cmd_line == **meta_chars
				&& *(*meta_chars + 1) == *(cmd_line + 1)))
			return (*meta_chars);
		meta_chars++;
	}
	return (NULL);
}
