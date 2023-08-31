int	lineCount(char **line)
{
	int	i;

	i = 0;
	while (line && line[i])
		i++;
	return (i);
}