#include "../../Include/minishell.h"


static char	*get_arg_from_env_value(char **envs, char *search_arg_name)
{
	char	*ptr;
	int		count;
	char	*temp_envs;

	count = 0;
	temp_envs = *envs;
	while (*temp_envs && *temp_envs != ':')
	{
		count++;
		temp_envs++;
		(*envs)++;
	}
	if (!count)
		return (NULL);
	if (**envs)
		(*envs)++;
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	ptr[count] = 0;
	while (--count > -1)
		ptr[count] = *(--temp_envs);
	str_addchar(&ptr, '/');
	own_strjoin(&ptr, search_arg_name);
	return (ptr);
}

static void	expand_from_env_value(char **dst, char *content) // find / path=.........
{
	char	*control_ptr;

	while (content && *content)
	{
		control_ptr = get_arg_from_env_value(&content, *dst);
		if (!access(control_ptr, F_OK))
		{
			free(*dst);
			*dst = control_ptr;
			return ;
		}
		free(control_ptr);
	}
}

void	expand_cmd(char **dst)
{
	t_env	*temp_env;

	temp_env = data.env_table;
	while (temp_env && *dst && **dst)
	{
		if (str_compare("PATH", temp_env->env_name))//
		{
			expand_from_env_value(dst, temp_env->content);//yola komutu ekliyor ve access fonksiyonu ile bu yol uzerinde o komut var mi diye kontrol ediyor
			return ;
		}
		temp_env = temp_env->next;
	}
}