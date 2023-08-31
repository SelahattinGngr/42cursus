/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initDestroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:18:12 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:18:14 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "unistd.h"

void	close_heradoc_file(void)
{
	if (g_data.heradoc_fd > SSTDERR)
	{
		g_data.heradoc_fd = close(g_data.heradoc_fd);
		g_data.heradoc_fd = 0;
	}
}
