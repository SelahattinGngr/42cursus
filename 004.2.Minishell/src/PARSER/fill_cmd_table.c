#include "../../Include/minishell.h"


static char	**create_path(t_lexlist *lex_list)
{
	int		count;
	char	**path;

	count = 0;
	while (lex_list && lex_list->type != SIGN_PIPE)
	{
		if (lex_list->type == TEXT && lex_list->content)
			count++;
		else
		{
			lex_list = lex_list->next;
			if (lex_list)
				lex_list = lex_list->next;
			continue ;
		}
		lex_list = lex_list->next;
	}
	if (!count)
		return (NULL);
	path = (char **)malloc(sizeof(char *) * (count + 1));
	path[count] = NULL;
	return (path);
}

static void	fill_cmdnode(t_cmdlist *node, t_lexlist **lex_list)
{
	char	**path_holder;
	int		is_begin;

	node->path = create_path(*lex_list);//ilk pipe oncesi komut uuxznlugu kadar bellek tahsili yaparak adres dondurur
	path_holder = node->path;
	is_begin = 0;
	while (*lex_list && (*lex_list)->type != SIGN_PIPE)
	{
		if (create_new_filelist(node, lex_list))//suanlik text oldugu icin 0 donuyor
			continue ;
		if (!(is_begin++) && (*lex_list)->content)
			expand_cmd(&((*lex_list)->content));//bu fonksiyon contenti yol ile birlestirir ve sonra boyle bir komut var mi diye kontrol eder(acces fonksiyonu)
		if ((*lex_list)->content)
			*(path_holder++) = (*lex_list)->content;// yeni parserlanmis yani find olarak degilde yol olarak acilmis pathi tutuyor
		*lex_list = (*lex_list)->next;
	}
	if (node->path)
		node->cmd = node->path[0];
}

void	fill_cmdTable(void)
{
	t_cmdlist	*tmp_cmdtable;
	t_lexlist	*tmp_lexlist;

	if (!data.cmd_table)
		return ;
	tmp_cmdtable = data.cmd_table;
	tmp_lexlist = data.lex_table;
	while (tmp_cmdtable)
	{
		fill_cmdnode(tmp_cmdtable, &tmp_lexlist);
		if (tmp_lexlist && *tmp_lexlist->content == *PIPE)
			tmp_lexlist = tmp_lexlist->next;
		tmp_cmdtable = tmp_cmdtable->next;
	}
}