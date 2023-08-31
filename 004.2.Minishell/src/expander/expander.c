#include "../../Include/minishell.h"


void	expand_envs(char **dst, char *ptr)
{
	t_env	*copy_envs;

	copy_envs = data.env_table;
	while (copy_envs)
	{
		if (str_compare(ptr, copy_envs->env_name))
		{
			own_strjoin(dst, copy_envs->content);
			break ;
		}
		copy_envs = copy_envs->next;
	}
}

static void	expand_order(char **dst, char **src)
{
	if (**src == *DOLLAR)
		expand_dollar(dst, src);
	else
		expand_envs(dst, "HOME");
}

static void	expand_text(t_lexlist *lex_table, int is_after_meta)
{
	char	*cmd;
	int		flag;
	char	*ptr;

	cmd = lex_table->content;
	ptr = NULL;
	flag = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && (!flag || flag == 1))
			flag = flag ^ 1;
		else if (*cmd == '\"' && (!flag || flag == 2))
			flag = flag ^ 2;
		else if ((!flag || flag == 2) && (*cmd == *DOLLAR || *cmd == *TILDA))
			expand_order(&ptr, &cmd);
		else
			str_addchar(&ptr, *cmd);
		cmd++;
	}
	if (is_after_meta && !ptr)
		return ;
	free(lex_table->content);
	lex_table->content = ptr;
}

static void	expand_values_from_lexlist(void)
{
	t_lexlist	*lex_table;

	lex_table = data.lex_table;
	while (lex_table)
	{
		if (lex_table->type == TEXT)
			expand_text(lex_table, 0);
		else if (lex_table->next && lex_table->type != SIGN_PIPE)
		{
			if (lex_table->type != SIGN_DOUBLE_LESS)
				expand_text(lex_table->next, 1);
			lex_table = lex_table->next;
		}
		lex_table = lex_table->next;
	}
}

void	expander(void)
{
	if (data.exec_output == 2)
		return ;
	expand_values_from_lexlist();
	clear_void_contents();
}