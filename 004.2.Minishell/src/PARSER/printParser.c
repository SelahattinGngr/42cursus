/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printParser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:13:28 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:13:30 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include "stdio.h"

static void	print_files(t_filelist *temp_filelist)
{
	while (temp_filelist)
	{
		printf("{fd: %d, ridrect : %s, filename : %s} ", temp_filelist->fd,
			temp_filelist->metachar, temp_filelist->filename);
		temp_filelist = temp_filelist->next;
	}
	printf("\n\n");
}

void	print_parser(void)
{
	int			node_count;
	int			index;
	t_cmdlist	*temp_cmdlist;

	node_count = 1;
	temp_cmdlist = g_data.cmd_table;
	while (temp_cmdlist)
	{
		index = 0;
		printf("------------NODE %d------------\n", node_count++);
		printf("PATH: ");
		while (temp_cmdlist->path && temp_cmdlist->path[index])
			printf("%s; ", (temp_cmdlist->path[index++]));
		printf("\nCMD: %s\n", temp_cmdlist->cmd);
		printf("infile: %d\n", temp_cmdlist->infile);
		printf("outfile: %d\n", temp_cmdlist->outfile);
		if (temp_cmdlist->heradoc_values)
			printf("heradoc values: %s\n", temp_cmdlist->heradoc_values);
		printf("pid: %d\n", temp_cmdlist->pid);
		printf("~files~\n");
		print_files(temp_cmdlist->files);
		temp_cmdlist = temp_cmdlist->next;
	}
}
