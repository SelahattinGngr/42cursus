/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:18:19 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:18:22 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "../../Include/myreadline.h"

static void	exit_signal_check(void)
{
	if (!g_data.input)
	{
		write(1, "Exit\n", 6);
		free_core();
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_core(env);
	g_data.input = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signalhandler);
	while (1)
	{
		update_loop();
		g_data.input = readline(g_data.title.full_title);
		exit_signal_check();
		lexer();
		expander();
		parser();
		executer();
		update_history(g_data.input);
		free_for_loop();
	}
	free_core();
	return (0);
}
