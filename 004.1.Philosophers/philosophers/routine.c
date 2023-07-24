/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 04:46:46 by segungor          #+#    #+#             */
/*   Updated: 2023/07/18 04:46:51 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->eat_count == philo->table->number_of_must_eat)
		return ;
	pthread_mutex_lock(philo->rfork);
	print(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->lfork);
	print(philo, TAKEN_FORK);
	print(philo, IS_EATING);
	pthread_mutex_lock(&philo->table->count_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->count_eat);
	time_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->eat_last);
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->table->eat_last);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	philo_sleep(t_philo *philo)
{
	print(philo, IS_SLEEPING);
	time_usleep(philo->table->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print(philo, IS_THINKING);
}

void	*philo_routine(void *_philo)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)_philo;
	if (philo->id % 2 == 0)
		time_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->table->stop_count);
		stop = philo->table->stop;
		pthread_mutex_unlock(&philo->table->stop_count);
		if (stop == 1)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
