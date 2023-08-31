#include "../../Include/minishell.h"

void	close_heradoc_file(void)
{
	if (data.heradoc_fd > SSTDERR)
	{
		data.heradoc_fd = close(data.heradoc_fd);
		data.heradoc_fd = 0;
	}
}