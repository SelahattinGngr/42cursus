/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:36:27 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:28 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "stdlib.h"
# include "../includes/cub3d.h"

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_calloc(t_game *game, size_t count, size_t size);
char	*ft_strjoin_free(char *s1, char *s2, t_game *game);
char	**ft_split(char const *s, char c, t_game *game);
char	*ft_strdup(const char *s1, t_game *game);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);

#endif