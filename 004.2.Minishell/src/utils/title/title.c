#include "../../../Include/minishell.h"

void	change_title(void)
{
	char	cwd[256];

	if (data.title.full_title)
		free(data.title.full_title);
	data.title.full_title = NULL;
	own_strjoin(&data.title.full_title, data.title.head);
	own_strjoin(&data.title.full_title, (char *)getcwd(cwd, 256));
	own_strjoin(&data.title.full_title, "$ ");
}

void	set_title(void)
{
	data.title.head = NULL;
	data.title.full_title = NULL;
	expand_envs(&data.title.head, "LOGNAME");
	str_addchar(&data.title.head, '@');
	expand_envs(&data.title.head, "NAME");
	str_addchar(&data.title.head, ':');
	own_strjoin(&data.title.full_title, data.title.head);
}
