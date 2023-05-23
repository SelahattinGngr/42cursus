/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:27:26 by segungor          #+#    #+#             */
/*   Updated: 2023/05/18 17:27:38 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;
	int	index;

	index = 0;
	len = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[index] != '\0')
		len += ft_putchar(str[index++]);
	return (len);
}

int	ft_itoa_base(unsigned long long nbr, int base, char *str, int mod)
{
	int	nbr_list[100];
	int	index;
	int	len;

	index = 0;
	len = 0;
	if (mod == 1 && (int)nbr < 0)
	{
		nbr *= -1;
		len += ft_putchar('-');
	}
	if (mod == 2)
		len += ft_putstr("0x");
	if (nbr == 0)
		len += ft_putchar('0');
	while (nbr)
	{
		nbr_list[index++] = nbr % base;
		nbr = nbr / base;
	}
	while (index--)
		len += ft_putchar(str[nbr_list[index]]);
	return (len);
}

int	ft_check_format(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'u')
		len += ft_itoa_base(va_arg(args, unsigned int), 10, "0123456789", 0);
	else if (format == 'd' || format == 'i' || format == 'u')
		len += ft_itoa_base(va_arg(args, int), 10, "0123456789", 1);
	else if (format == 'p')
		len += ft_itoa_base(va_arg(args, unsigned long long), 16,
				"0123456789abcdef", 2);
	else if (format == 'x')
		len += ft_itoa_base(va_arg(args, unsigned int), 16,
				"0123456789abcdef", 0);
	else if (format == 'X')
		len += ft_itoa_base(va_arg(args, unsigned int), 16,
				"0123456789ABCDEF", 0);
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		index;
	int		len;
	va_list	args;

	index = 0;
	len = 0;
	va_start(args, str);
	while (str[index] != '\0')
	{
		if (str[index] == '%')
		{
			index++;
			len += ft_check_format(args, str[index]);
		}
		else
			len += ft_putchar(str[index]);
		index++;
	}
	va_end(args);
	return (len);
}
