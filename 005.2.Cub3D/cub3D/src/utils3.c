/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:36:03 by segungor          #+#    #+#             */
/*   Updated: 2024/01/20 15:10:30 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "limits.h"
#include "../includes/error.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < (size - 1) && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

static int	ft_isspace(char chr)
{
	if ((chr >= 9 && chr <= 13) || chr == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned long	ret_val;
	int				index;
	int				flag;

	flag = 1;
	index = 0;
	if (*nptr == '\0')
		return (0);
	while (ft_isspace(nptr[index]))
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			flag *= -1;
		index++;
	}
	ret_val = 0;
	while (nptr[index] >= '0' && nptr[index] <= '9')
		ret_val = (ret_val * 10) + (nptr[index++] - '0');
	if (ret_val > LONG_MAX && flag == -1)
		return (0);
	if (ret_val > LONG_MAX && flag == 1)
		return (-1);
	return (ret_val * flag);
}
