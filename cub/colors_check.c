/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* colors_check.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/09/25 14:39:57 by eabourao          #+#    #+#             */
/* Updated: 2025/09/25 17:51:13 by eabourao         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_calc_size(t_cub3d *info, char p)
{
	int	l;
	int	c;

	c = 0;
	l = 0;
	if (p == 'c')
		l = info->ceiling + 2;
	else if (p == 'f')
		l = info->floor + 2;
	while (info->map_coord[l] && info->map_coord[l] != '\n')
	{
		c++;
		l++;
	}
	return (c);
}

int	count_strings(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	ft_is_all_digits(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ')
		i++;
	return (str[i] == '\0');
}

int	ft_atoi_color(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 255)
			return (256);
		i++;
	}
	return ((int)res);
}

void	validate_color_values(char **split, t_cub3d *info, char f_or_c)
{
	int	r;
	int	g;
	int	b;

	if (!ft_is_all_digits(split[0])
		|| !ft_is_all_digits(split[1])
		|| !ft_is_all_digits(split[2]))
		return (info->error = 1, (void)0);
	r = ft_atoi_color(split[0]);
	g = ft_atoi_color(split[1]);
	b = ft_atoi_color(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (info->error = 1, (void)0);
	if (f_or_c == 'F')
		info->floor = (r << 16) | (g << 8) | b;
	else if (f_or_c == 'C')
		info->ceiling = (r << 16) | (g << 8) | b;
}


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

void	check_color_line(t_cub3d *info,	 char type)
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
