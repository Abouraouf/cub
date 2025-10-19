/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:02:28 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/18 15:40:07 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	process_and_validate_split(char *line, t_cub3d *info, char f_or_c)
{
	char	**split_colors;
	char	temp_line[100];

	ft_strlcpy(temp_line, line, ft_calc_size(info, f_or_c) + 1);
	split_colors = ft_split(temp_line, ',');
	if (count_strings(split_colors) != 3)
	{
		ft_free(split_colors);
		info->error = 1;
		return ;
	}
	validate_color_values(split_colors, info, f_or_c);
	ft_free(split_colors);
}

void	check_color_line(t_cub3d *info, char type)
{
	char	*line_start;
	int		i;
	int		comma_count;

	if (type == 'f')
	{
		line_start = info->map_coord + info->floor + 2;
	}
	else
		line_start = info->map_coord + info->ceiling + 2;
	i = 0;
	comma_count = 0;
	while (line_start[i] && line_start[i] != '\n')
	{
		if (line_start[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
	{
		info->error = 1;
		return ;
	}
	if (!info->error)
		process_and_validate_split(line_start, info, type);
}

void	ft_check_limits_floor(t_cub3d	*info)
{
	check_color_line(info, 'f');
}

void	ft_check_limits_ceiling(t_cub3d *info)
{
	check_color_line(info, 'c');
}
