#include "../../Include/minishell.h"

/*
	global degiskende ki metachars degiskenine 2 boyutlu bir dizi olusturur
	ve icerisine teker teker belirlenen metakarakterleri atar.
	metakarakterler sirasiyla ">>", "<<", "<", ">", "|"'dir
*/
static void	set_metachars(void)
{
	char	**meta_list;

	meta_list = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1));
	data.metachars = meta_list;
	*(meta_list++) = ft_strdup(DOUBLE_GREAT);
	*(meta_list++) = ft_strdup(DOUBLE_LESS);
	*(meta_list++) = ft_strdup(SINGLE_LESS);
	*(meta_list++) = ft_strdup(SINGLE_GREAT);
	*(meta_list++) = ft_strdup(PIPE);
	*(meta_list++) = NULL;
}

void	init_core(char **env)
{
	fill_envs(env);
	set_metachars();
	set_title();
	data.exec_output = 0;
	data.old_exec_output = 0;
	data.main_pid = getpid();
}