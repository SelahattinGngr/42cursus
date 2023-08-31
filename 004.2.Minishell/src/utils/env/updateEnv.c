#include "../../../Include/minishell.h"

int	update_env(char *env_name, char *new_arg)
{
	t_env	*env;

	env = data.env_table;
	while (env)
	{
		if (str_compare(env->env_name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			own_strjoin(&env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
