/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 05:01:52 by segungor          #+#    #+#             */
/*   Updated: 2023/07/19 13:41:45 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_check_data(void)
{
	ft_printf(" ____________________________________________________ \n");
	ft_printf("|            Please enter 4 or 5 arguments           |\n");
	ft_printf("|____________________________________________________|\n");
	ft_printf("|             [1][Number of philosophers]            |\n");
	ft_printf("|             [2][Time to die]                       |\n");
	ft_printf("|             [3][Time to eat]                       |\n");
	ft_printf("|             [4][Time to sleep]                     |\n");
	ft_printf("|             [5][Number of meals]                   |\n");
	ft_printf("|____________________________________________________|\n");
}

int	ft_start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_time();
	while (i < data->nbr_philo)
	{
		data->philo.philo_ind = i;
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] == -1)
		{
			while (--i >= 0)
				kill(data->pid_philo[i], SIGKILL);
			return (1);
		}
		else if (data->pid_philo[i] == 0)
		{
			ft_init_philo(data);
			ft_routine(data);
		}
		i++;
	}
	sem_wait(data->stop);
	return (0);
}

static void	ft_kill_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		kill(data->pid_philo[i], SIGKILL);
		i++;
	}
	if (data->pid_philo)
		free(data->pid_philo);
}

static int	ft_check_valid(int ac, char **av)
{
	size_t	i;

	if (ac < 5 || ac > 6)
	{
		ft_check_data();
		return (1);
	}
	i = 1;
	while (av[i])
	{
		if (!ft_is_digit(av[i]) || (!ft_atoi(av[i])))
		{
			ft_printf("Invalid argument\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_check_valid(ac, av))
		return (1);
	if (ft_init_datas(&data, ac, av) == 1)
		return (1);
	if (ft_start_philo(&data))
		return (1);
	ft_kill_philosophers(&data);
	return (0);
}
