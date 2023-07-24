/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 04:49:18 by segungor          #+#    #+#             */
/*   Updated: 2023/07/18 05:01:37 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_atoi_base(unsigned long int num)
{
	if (num >= 10)
		ft_atoi_base(num / 10);
	ft_putchar((num % 10) + 48);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		write(1, s++, 1);
	}
}

int	ft_printf(char *arr, ...)
{
	va_list	arg;

	va_start(arg, arr);
	while (*arr)
	{
		if (*arr == '%')
		{
			arr++;
			if (*arr == 'd')
				ft_atoi_base(va_arg(arg, unsigned long int));
			if (*arr == 's')
				ft_putstr(va_arg(arg, char *));
		}
		else
			ft_putchar(*arr);
		arr++;
	}
	va_end(arg);
	return (0);
}
