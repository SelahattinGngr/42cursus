#include "../../../Include/minishell.h"

void	print_error(char *ptr1, char *ptr2, char *ptr3)
{
	if (ptr1)
		write(2, ptr1, ft_strlen(ptr1));
	if (ptr2)
		write(2, ptr2, ft_strlen(ptr2));
	if (ptr3)
		write(2, ptr3, ft_strlen(ptr3));
}

int	print_lex_error(t_lexlist *lex_list)
{
	print_error("-bash: syntax error near unexpected token '",
		lex_list->content, "'\n");
	data.exec_output = 2;
	free_lexer_without_heradoc(lex_list);
	return (0);
}
