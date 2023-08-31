#include "../../../Include/minishell.h"

/*
	gonderilen karakter dizisi ile metakarakterleri kıyaslar
	eger var ise olan metakarakteri return eder.
*/
char	*compare_metachars(char *cmd_line)
{
	char	**meta_chars;

	if (!cmd_line)
		return (NULL);
	meta_chars = data.metachars;
	while (meta_chars && *meta_chars)
	{
		if ((*cmd_line == **meta_chars && !*(*meta_chars + 1))
			|| (*cmd_line == **meta_chars
				&& *(*meta_chars + 1) == *(cmd_line + 1)))
			return (*meta_chars);
		meta_chars++;
	}
	return (NULL);
}
