/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:21:47 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:21:51 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	min;
	size_t	max;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	min = 0;
	max = ft_strlen(s1) - 1;
	while (s1[min] != '\0' && ft_strchr(set, s1[min]) != NULL)
		min++;
	while (max >= min && ft_strchr(set, s1[max]) != NULL)
		max--;
	if (max < min || s1[0] == '\0')
		s2 = (char *)ft_calloc(1, sizeof(char));
	else
		s2 = malloc(sizeof(char) * (max - min + 2));
	if (s2 == NULL)
		return (NULL);
	if (max >= min && s1[0] != '\0')
	{
		ft_memcpy(s2, s1 + min, max - min + 1);
		s2[max - min + 1] = '\0';
	}
	return (s2);
}
