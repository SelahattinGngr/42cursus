/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:30:34 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:30:36 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	*exit_status_pointer(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}

void	exec_exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*exit_status_pointer() = status;
}

int	exec_exit_status_get(void)
{
	return (*exit_status_pointer());
}
