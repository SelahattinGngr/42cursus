/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 04:53:13 by segungor          #+#    #+#             */
/*   Updated: 2023/07/18 05:01:42 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_init_eatthread(t_data *data)
{
	if (pthread_create(&data->mealchecker_tid, NULL,
			&ft_eating_checker, data))
	{
		ft_printf("Error pthread");
		return (1);
	}
	pthread_detach(data->mealchecker_tid);
	return (0);
}

void	ft_init_philo(t_data *data)
{
	data->philo.time_of_last_meal = ft_time();
	if (pthread_create(&data->deathchecker_tid, NULL, &ft_death_checker, data))
	{
		ft_printf("Error pthread");
		sem_post(data->stop);
	}
	pthread_detach(data->deathchecker_tid);
}

static int	ft_init_sempahore(t_data *data)
{
	sem_unlink("fork_sem");
	sem_unlink("write_sem");
	sem_unlink("stop");
	sem_unlink("eat_enough");
	data->fork_sem = sem_open("fork_sem", O_CREAT | O_EXCL,
			0666, data->nbr_philo);
	data->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, 0666, 1);
	data->stop = sem_open("stop", O_CREAT | O_EXCL, 0666, 0);
	if (data->nbr_of_meals)
		data->eat_enough = sem_open("eat_enough", O_CREAT | O_EXCL, 0666, 0);
	return (0);
}

int	ft_init_datas(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nbr_of_meals = -1;
	if (ac == 6)
		data->nbr_of_meals = ft_atoi(av[5]);
	data->pid_philo = malloc(sizeof(pid_t) * data->nbr_philo);
	memset(data->pid_philo, 0, sizeof(pid_t) * data->nbr_philo);
	ft_init_sempahore(data);
	ft_init_eatthread(data);
	return (0);
}
