/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:15:09 by segungor          #+#    #+#             */
/*   Updated: 2022/12/22 22:15:10 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*rslt;
	int		len;

	i = 0;
	rslt = (char *)s;
	len = (ft_strlen(s));
	while (i <= len)
	{
		if (rslt[len] == (char)c)
			return (rslt + len);
		len--;
	}
	return (NULL);
}
