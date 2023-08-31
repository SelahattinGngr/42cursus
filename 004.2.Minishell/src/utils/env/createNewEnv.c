#include "../../../Include/minishell.h"

/*
	bağlı liste yapısında henüz bir bode yok is onu yaratır
	var is sonuna gider ve ardına yeni bir node ekler.
	Gelen parametreyi oraya ekler.
*/
t_env	*add_newenv(t_env **env_table, char *env)
{
	t_env	*last_node;
	char	*content;

	if (!*env_table)
	{
		*env_table = (t_env *)malloc(sizeof(t_env));
		last_node = *env_table;
	}
	else
	{
		last_node = *env_table;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = (t_env *)malloc(sizeof(t_env));
		last_node = last_node->next;
	}
	last_node->env_name = get_env_name(env);
	content = env + ft_strlen(last_node->env_name);
	if (*content == '=' && *(content + 1))
		last_node->content = ft_strdup(content + 1);
	else
		last_node->content = NULL;
	last_node->next = NULL;
	return (last_node);
}

/*
	mainde 3.parametre olarak aldığımız env değişkenini alır
	ve bağlı liste yapısına doldurur.
*/
void	fill_envs(char **env)
{
	while (env && *env)
		add_newenv(&data.env_table, *(env++));
}
