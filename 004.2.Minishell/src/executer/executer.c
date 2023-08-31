#include "../../Include/minishell.h"

void	clear_pipe(int *fd)
{
	int	index;

	if (fd)
	{
		index = -1;
		while (++index < 6)
		{
			if (fd[index])
				close(fd[index]);
		}
		free(fd);
	}
}

static int	*create_pipe(void)
{
	int		index;
	int		*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
}

static void	switch_pipe(int **fd)
{
	(*fd)[0] = (*fd)[0] ^ (*fd)[2];
	(*fd)[2] = (*fd)[0] ^ (*fd)[2];
	(*fd)[0] = (*fd)[0] ^ (*fd)[2];
	(*fd)[1] = (*fd)[1] ^ (*fd)[3];
	(*fd)[3] = (*fd)[1] ^ (*fd)[3];
	(*fd)[1] = (*fd)[1] ^ (*fd)[3];
	(*fd)[5] = (*fd)[5] ^ (*fd)[3];
	(*fd)[3] = (*fd)[5] ^ (*fd)[3];
	(*fd)[5] = (*fd)[5] ^ (*fd)[3];
	(*fd)[4] = (*fd)[2] ^ (*fd)[4];
	(*fd)[2] = (*fd)[2] ^ (*fd)[4];
	(*fd)[4] = (*fd)[2] ^ (*fd)[4];
}

static void	run_multiple_command(t_cmdlist *cmd_list)
{
	int			*fd;

	fd = create_pipe();
	while (cmd_list)
	{
		switch_pipe(&fd);
		pipe(&fd[2]);
		cmd_list->pid = fork();
		if (cmd_list->pid <= 0)
			run_process(cmd_list, fd, 2);
		cmd_list = cmd_list->next;
		if (fd[4] && fd[5])
		{
			close(fd[4]);
			close(fd[5]);
			fd[4] = 0;
			fd[5] = 0;
		}
	}
	clear_pipe(fd);
	wait_all();
}

static void	run_single_command(t_cmdlist *cmd_list, int *fd)
{
	if (cmd_list->infile != SSTDERR && cmd_list->outfile != SSTDERR)
		exec_command(cmd_list, fd, -1);
}

void	executer(void)
{
	if (!data.cmd_table)
		return ;
	else if (!data.cmd_table->next)
		run_single_command(data.cmd_table, NULL);
	else
		run_multiple_command(data.cmd_table);
}