/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 05:01:31 by segungor          #+#    #+#             */
/*   Updated: 2023/07/18 05:01:31 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_taking_forks_eating(t_data *data)
{
	sem_wait(data->fork_sem);
	sem_wait(data->fork_sem);
	sem_wait(data->write_sem);
	ft_printf("%d %d has taken a fork\n", \
		ft_time() - data->start_time, data->philo.philo_ind + 1);
	ft_printf("%d %d has taken a fork\n", \
		ft_time() - data->start_time, data->philo.philo_ind + 1);
	sem_post(data->write_sem);
	sem_wait(data->write_sem);
	ft_printf("%d %d is eating\n", ft_time() - data->start_time, \
		data->philo.philo_ind + 1);
	sem_post(data->write_sem);
	data->philo.time_of_last_meal = ft_time();
	data->philo.total_nbr_of_meals += 1;
	if (data->philo.total_nbr_of_meals == data->nbr_of_meals)
		sem_post(data->eat_enough);
	ft_usleep(data->time_to_eat);
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
}

void	ft_sleeping_thinking(t_data *data)
{
	sem_wait(data->write_sem);
	ft_printf("%d %d is sleeping\n", \
		ft_time() - data->start_time, data->philo.philo_ind + 1);
	sem_post(data->write_sem);
	ft_usleep(data->time_to_sleep);
	sem_wait(data->write_sem);
	ft_printf("%d %d is thinking\n", \
		ft_time() - data->start_time, data->philo.philo_ind + 1);
	sem_post(data->write_sem);
}

void	*ft_routine(void *data)
{
	t_data	*philo;

	philo = (t_data *)data;
	philo->start_time = ft_time();
	while (1)
	{
		ft_taking_forks_eating(philo);
		ft_sleeping_thinking(philo);
	}
	return (NULL);
}

void	*ft_eating_checker(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	i = -1;
	sem_wait(data->write_sem);
	while (++i < data->nbr_philo)
	{
		sem_post(data->write_sem);
		sem_wait(data->eat_enough);
		sem_wait(data->write_sem);
	}
	sem_post(data->stop);
	return (NULL);
}

void	*ft_death_checker(void *arg)
{
	t_data	*data;
	long	time_now;

	data = arg;
	while (1)
	{
		time_now = ft_time();
		if (time_now - data->philo.time_of_last_meal >= data->time_to_die)
		{
			sem_wait(data->write_sem);
			ft_printf("%d %d died\n", \
				ft_time() - data->start_time, data->philo.philo_ind + 1);
			sem_post(data->stop);
			exit(0);
		}
	}
	return (NULL);
}
