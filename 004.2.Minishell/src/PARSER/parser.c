/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:13:21 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:13:23 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdlib.h"

void	parser(void)
{
	g_data.cmd_table = NULL;
	create_cmdtable(g_data.lex_table);
	fill_cmdtable();
	create_files(g_data.cmd_table);
}
