/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:10:32 by segungor          #+#    #+#             */
/*   Updated: 2022/12/22 22:10:34 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print(int n, int fd)
{
	char	c;
	int		t;

	t = n;
	if (t > 9)
	{
		t = print((t / 10), fd);
	}
	c = (n % 10) + 48;
	write(fd, &c, 1);
	return (t);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
		print(n, fd);
	}
	else
		print(n, fd);
}
