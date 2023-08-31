#include "../../Include/minishell.h"

void	print_lexer(void)
{
	t_lexlist	*lexer_temp;

	lexer_temp = data.lex_table;
	printf ("~LEXER TABLE~\n");
	while (lexer_temp)
	{
		printf("{type: %d, content: %s}\n", lexer_temp->type,
			lexer_temp->content);
		lexer_temp = lexer_temp->next;
	}
	printf("\n\n");
}
