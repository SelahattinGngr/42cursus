/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:29:24 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:29:25 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtin.h"
#include "../inc/envv.h"

int	builtin_env(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	int	i;

	if (g_env == NULL)
	{
		print_error(SHELL_NAME, "env", NULL, "environ not set");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (g_env[i])
	{
		ft_putendl_fd(g_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
