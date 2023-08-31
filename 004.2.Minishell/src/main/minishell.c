#include "../../Include/minishell.h"

static void exit_signal_check()
{
	if (!data.input)
	{
		write(1, "Exit\n", 6);
		free_core();
		exit(EXIT_SUCCESS);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	init_core(env);
	data.input = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signalhandler);
	while (1)
	{
		update_loop();
		data.input = readline(data.title.full_title);
		exit_signal_check();
		lexer();
		expander();
		parser();
		executer();
		update_history(data.input);
		free_for_loop();
	}
	free_core();
}