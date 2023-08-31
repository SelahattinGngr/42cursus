#include "../../../Include/minishell.h"

void	free_env_cpy(char **envlist)
{
	char	**temp_envlist;

	temp_envlist = envlist;
	while (*temp_envlist)
		free(*(temp_envlist++));
	free(envlist);
}

void	free_metachars(void)
{
	char	**temp_metachars;

	temp_metachars = data.metachars;
	if (!temp_metachars)
		return ;
	while (temp_metachars && *temp_metachars)
		free(*(temp_metachars++));
	free(data.metachars);
}

void	free_envtable(void)
{
	t_env	*env;
	t_env	*temp_env;

	env = data.env_table;
	while (env)
	{
		temp_env = env;
		env = env->next;
		free(temp_env->env_name);
		free(temp_env->content);
		free(temp_env);
	}
}

void	free_title(void)
{
	free(data.title.full_title);
	free(data.title.head);
}