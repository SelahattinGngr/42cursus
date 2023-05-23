/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:27:57 by segungor          #+#    #+#             */
/*   Updated: 2023/05/18 17:28:56 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig)
{
	static int	index;
	static char	chr;

	if (sig == SIGUSR1)
		chr = (chr << 1) | 1;
	else if (sig == SIGUSR2)
		chr = (chr << 1);
	index++;
	if (index == 8)
	{
		ft_printf("%c", chr);
		index = 0;
		chr = 0;
	}
}

int	main(void)
{
	ft_printf("SERVER : Server started\nPID -> %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
