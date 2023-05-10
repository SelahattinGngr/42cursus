/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:09:06 by segungor          #+#    #+#             */
/*   Updated: 2022/12/22 22:09:08 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstc;
	unsigned char	*srcc;

	if (!dst && !src)
		return (NULL);
	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	if (dst < src)
		while (len--)
			*dstc++ = *srcc++;
	else
	{
		srcc = (unsigned char *)src + (len -1);
		dstc = (unsigned char *)dst + (len -1);
		while (len--)
			*dstc-- = *srcc--;
	}
	return (dst);
}
