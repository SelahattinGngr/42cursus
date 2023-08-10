/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:37:50 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:37:52 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../inc/global.h"
#include "../inc/env.h"
#include "../inc/envv.h"
#include "../inc/exec.h"
#include "../inc/lexer.h"
#include "../inc/parser.h"
#include "../inc/signals.h"

static char	*get_input(void)
{
	char	*input;
	char	*prompt;

	prompt = env_get_value("PS1");
	if (prompt == NULL)
		prompt = PROMPT;
	input = readline(prompt);
	if (input == NULL)
		return (NULL);
	else if (input && input[0])
		add_history(input);
	return (input);
}

static void	process_input(char *input)
{
	t_list	*l_token;
	t_list	*l_parser;

	signal(SIGINT, SIG_IGN);
	errno = 0;
	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input);
	free(input);
	if (l_token != NULL)
		l_parser = parser(l_token);
	if (l_token != NULL && l_parser != NULL)
		exec_recursive(l_parser, false, l_parser);
	if (l_parser != NULL)
		ft_lstclear(&l_parser, c_cmd_destroy);
	else if (l_token != NULL)
		ft_lstclear(&l_token, c_token_destroy);
}

int	main(void)
{
	char	*input;

	g_env = NULL;
	signal(SIGQUIT, SIG_IGN);
	if (env_init() == ERROR)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, signal_ctlc);
		termios_change(false);
		input = get_input();
		if (input == NULL)
		{
			if (isatty(STDERR_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			termios_change(true);
			break ;
		}
		process_input(input);
	}
	rl_clear_history();
	if (g_env)
		ft_free_split(&g_env);
	exit(exec_exit_status_get());
}
