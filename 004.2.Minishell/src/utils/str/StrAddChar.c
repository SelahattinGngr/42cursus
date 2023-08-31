/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrAddChar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:20:54 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:20:55 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
#include "stdlib.h"

void	str_addchar(char **dst, char c)
{
	char	*ptr;
	char	*holder_ptr;
	char	*holder_dst;
	int		len;

	len = ft_strlen(*dst) + 1;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	holder_ptr = ptr;
	holder_dst = *dst;
	while (holder_dst && *holder_dst)
		*(holder_ptr++) = *(holder_dst++);
	*(holder_ptr++) = c;
	*(holder_ptr++) = 0;
	if (*dst)
		free(*dst);
	*dst = ptr;
}
