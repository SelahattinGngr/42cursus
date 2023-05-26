/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:12:25 by segungor          #+#    #+#             */
/*   Updated: 2023/05/11 13:36:19 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dizi;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	dizi = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dizi == NULL)
		return (NULL);
	while (s1[++i])
		dizi[i] = s1[i];
	while (s2[j])
		dizi[i++] = s2[j++];
	dizi[i] = '\0';
	return (dizi);
}
