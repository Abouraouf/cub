/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:25 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/25 14:03:30 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	possible_character(t_cub3d *info)
{
	int			i;
	int			flag;

	flag = 0;
	i = info->place_map - 1;
	while (info->map_coord[i])
	{
		if (info->map_coord[i] == 'N')
		{
			if (flag == 0)
				flag = 1;
			else
				return ((void)(info->error = 1));
		}
		else if (info->map_coord[i] != '1' && info->map_coord[i] != '0'
			&& info->map_coord[i] != ' ' && info->map_coord[i] != '\n')
			return ((void)(info->error = 1));
		if (info->map_coord[i] == '\n' && info->map_coord[i + 1] == '\n')
			return ((void)(info->error = 1));
		i++;
	}
	info->error = 0;
}
