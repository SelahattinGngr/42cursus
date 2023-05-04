/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:55:20 by segungor          #+#    #+#             */
/*   Updated: 2023/05/04 01:57:22 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ber_control(char *map_name)
{
	int	arg_len;

	arg_len = ft_strlen(map_name);
	if (map_name[arg_len - 1] != 'r' || map_name[arg_len - 2] != 'e'
		|| map_name[arg_len - 3] != 'b' || map_name[arg_len - 4] != '.')
		err_msg("map Must have .ber extension");
}

void	tmp_control(char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		err_msg("Map not found");
	close(fd);
}

void	map_control(char *map_name, t_game *data)
{
	ber_control(map_name);
	data->maplocation = ft_strjoin("map/", map_name);
	tmp_control(data->maplocation);
}
