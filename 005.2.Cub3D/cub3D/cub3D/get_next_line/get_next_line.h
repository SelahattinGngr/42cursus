/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:37:38 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:53 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../includes/cub3d.h"

char	*get_next_line(t_game *game, int fd);
char	*get_new_line(t_game *game, char *buffer);
char	*strjoin(t_game *game, char *buffer, char *new_buffer);
char	*get_new_buffer(t_game *game, char *buffer);
int		find_nl_char(char *buffer);

#endif
