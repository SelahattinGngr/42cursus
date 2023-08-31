/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:16:35 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:16:38 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	classify(t_lexlist *lex_table)
{
	char	*metachars;

	if (!lex_table)
		return ;
	while (lex_table)
	{
		metachars = compare_metachars(lex_table->content);
		if (metachars)
		{
			lex_table->type = (*metachars - 1) * ft_strlen(metachars);
		}
		else
			lex_table->type = 0;
		lex_table = lex_table->next;
	}
}
