#include "../../Include/minishell.h"


/*
	token listesindeki içeriği boş olan elemanları temizlemektir. 
	Bu tür boş elemanlar, lexer veya diğer aşamalardaki işlemler sırasında 
	hatalı veya gereksiz veri oluştuğunda ortaya çıkabilir.
*/
void	clear_void_contents(void)
{
	t_lexlist	*lex_list;
	t_lexlist	*temp_lex_list;

	lex_list = data.lex_table;
	temp_lex_list = data.lex_table;
	while (lex_list)
	{
		if (!lex_list->content)
		{
			if (lex_list == data.lex_table)
			{
				data.lex_table = data.lex_table->next;
				temp_lex_list = temp_lex_list->next;
			}
			else
				temp_lex_list->next = lex_list->next;
			free(lex_list);
			lex_list = temp_lex_list;
		}
		temp_lex_list = lex_list;
		if (lex_list)
			lex_list = lex_list->next;
	}
}