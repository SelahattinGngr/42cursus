/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimSpace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:22:11 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:22:12 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

size_t	trim_spaces(char **cmd_line)
{
	size_t	count;

	count = 0;
	if (!*cmd_line)
		return (count);
	while (**cmd_line == 32)
	{
		count++;
		(*cmd_line)++;
	}
	return (count);
}
