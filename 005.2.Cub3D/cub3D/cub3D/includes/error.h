/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:36:31 by segungor          #+#    #+#             */
/*   Updated: 2024/01/18 17:40:16 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "cub3d.h"

void	exit_err(char *err_msg, t_game *game);
void	free_exit_err(char *err_msg, t_game *game);

#endif