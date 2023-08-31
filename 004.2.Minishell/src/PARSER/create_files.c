#include "../../Include/minishell.h"


static int	check_directory_error(char *file_name)
{
	char	*temp_file_name;

	temp_file_name = file_name;
	while (file_name && *file_name)
	{
		if (*(file_name++) == '/')
		{
			print_error("-bash: ", temp_file_name, ": Is a directory\n");
			return (0);
		}
	}
	return (1);
}

static int	raise_file_error(t_filelist *file, int *file_output)
{
	int		error;

	error = 0;
	if (!check_directory_error(file->filename))
		error = 1;
	if (!error && *file->filename == '\"')
	{
		error = 1;
		print_error("-bash: : No such file or directory\n", NULL, NULL);
	}
	else if (!error && *file->filename == '$')
	{
		error = 1;
		print_error("-bash: ", file->filename, ": ambiguous redirect\n");
	}
	if (!error)
		return (error);
	file->fd = SSTDERR;
	*file_output = file->fd;
	return (error);
}

static void	create_infile(t_cmdlist *node, t_filelist *file)
{
	char	*pwd;
	char	ptr[256];

	if (file->metachar[1] == DOUBLE_LESS[1])
	{
		node->infile = HERADOC;
		return ;
	}
	if (raise_file_error(file, &node->infile))
		return ;
	pwd = NULL;
	own_strjoin(&pwd, (char *)getcwd(ptr, 256));
	str_addchar(&pwd, '/');
	own_strjoin(&pwd, file->filename);
	if (!access(pwd, F_OK))
		file->fd = open(pwd, O_RDONLY, 0777);
	if (file->fd <= SSTDERR && file->fd != HERADOC)
	{
		print_error("-bash: ", file->filename,
			": No such file or directory\n");
		data.exec_output = 1;
		file->fd = SSTDERR;
	}
	node->infile = file->fd;
	free(pwd);
}

static void	create_outfile(t_cmdlist *node, t_filelist *file)
{
	char	*outfile_path;
	char	ptr[256];

	if (raise_file_error(file, &node->outfile))
		return ;
	outfile_path = NULL;
	own_strjoin(&outfile_path, (char *)getcwd(ptr, 256));
	str_addchar(&outfile_path, '/');
	own_strjoin(&outfile_path, file->filename);
	if (file->metachar[1] == DOUBLE_GREAT[1])
		file->fd = open(outfile_path,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file->fd = open(outfile_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	node->outfile = file->fd;
	free(outfile_path);
}

void	create_files(t_cmdlist *node)
{
	t_filelist *tmp_file;

	if (!node)
		return ;
	run_heradocs(node);
	if (data.exec_output || !node)
		return ;
	while (node)
	{
		tmp_file = node->files;
		while (tmp_file)
		{
			if (*tmp_file->metachar == *SINGLE_GREAT)
				create_outfile(node, tmp_file);
			else
				create_infile(node, tmp_file);
			if (tmp_file->fd == SSTDERR)
			{
				data.exec_output = 1;
				break ;
			}
			tmp_file = tmp_file->next;
		}
		node = node->next;
	}
}