/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:21:43 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:21:44 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
#include "stdlib.h"

char	*ft_strpcpy(char *dst, char *src, int count)
{
	char	*ptr;
	char	*return_ptr;
	int		index;

	if (!src || !count)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(dst) + count + 1));
	return_ptr = ptr;
	index = -1;
	while (dst && *dst)
		*(ptr++) = *(dst++);
	while (++index < count && src && *src)
		*(ptr++) = *(src++);
	*ptr = 0;
	return (return_ptr);
}
