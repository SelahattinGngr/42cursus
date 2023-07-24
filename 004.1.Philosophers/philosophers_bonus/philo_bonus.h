/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 04:57:05 by segungor          #+#    #+#             */
/*   Updated: 2023/07/18 05:02:03 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <stdarg.h>

typedef struct s_philo
{
	size_t		philo_ind;
	size_t		total_nbr_of_meals;
	time_t		time_of_last_meal;
	int			nbr_of_meals;
}	t_philo;

typedef struct s_arg
{
	pthread_t	mealchecker_tid;
	pthread_t	deathchecker_tid;	
	pid_t		*pid_philo;
	sem_t		*write_sem;
	sem_t		*fork_sem;
	sem_t		*stop;
	sem_t		*eat_enough;
	int			nbr_philo;
	time_t		start_time;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	size_t		nbr_of_meals;
	t_philo		philo;
}	t_data;

void	ft_taking_forks_eating(t_data *data);
void	ft_sleeping_thinking(t_data *data);
void	*ft_routine(void *data);
void	*ft_eating_checker(void *arg);
void	*ft_death_checker(void *arg);
void	ft_usleep(int ms);
void	ft_init_philo(t_data *data);

long	ft_time(void);
int		ft_init_datas(t_data *data, int ac, char **av);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);
int		ft_printf(char *arr, ...);

#endif
