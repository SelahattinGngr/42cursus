/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:29:12 by segungor          #+#    #+#             */
/*   Updated: 2023/05/18 17:29:18 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_decode(int signum, siginfo_t *inf, void *context)
{
	static int	index;
	static char	chr;

	(void)context;
	if (signum == SIGUSR1)
		chr = (chr << 1) | 1;
	else if (signum == SIGUSR2)
		chr = (chr << 1);
	index++;
	if (index == 8)
	{
		ft_printf("%c", chr);
		kill (inf->si_pid, SIGUSR2);
		chr = 0;
		index = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_decode;
	ft_printf("SERVER : Server started\nPID -> %d\n", getpid());
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
