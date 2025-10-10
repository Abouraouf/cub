/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:25 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/10 14:22:23 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_if_player(char *str)
{
	if (*str == 'N' || *str == 'S'
		|| *str == 'E' || *str == 'W')
		return (1);
	else
		return (0);
}

void    ft_check_if_empty(t_cub3d *info)
{
	int	i;
	int	has_content_on_line;

	has_content_on_line = 0;
	i = info->place_map;
	while (info->map_coord[i])
	{
		if (info->map_coord[i] != ' ')
			has_content_on_line = 1;
		if (info->map_coord[i] == '\n')
		{
			if (has_content_on_line == 0)
			{
				info->error = 1;
				return ;
			}
			has_content_on_line = 0;
		}
		i++;
	}
}

int	ft_check_surr(char **str, int j, int i)
{
	int	length;

	length = ft_strlen(str[i]);
	if (str[i][j] == '0' || check_if_player(str[i] + j))
	{
		if (str[i + 1][j] == ' ' || str[i - 1][j] == ' ' || j >= (int)ft_strlen(str[i - 1]))
			return (0);
		if (str[i][j + 1] && ((str[i][j + 1] == ' ') || (str[i][j - 1] == ' ') || j >= (int)ft_strlen(str[i + 1])))
			return (0);
		if (!str[i][j + 1])
			return (0);
		else
			return (1);
	}
	return (1);
}

int	calculate_lines(char **str) // get back here
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	j = 0;
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j] && flag == 0)
		{
			if (check_if_player(str[i] + j) || str[i][j] == '0'
				|| str[i][j] == '1')
			{
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag == 0)
			return (i);
		else
			flag = 0;
	}
	return (i - 1);
}

void	check_after_finish(t_cub3d *info, int i)
{
	while (info->map_coord[i])
	{
		if (info->map_coord[i] == ' ')
			return ((void)(info->error = 0));
		else
			return ((void)(info->error = 1));
		i++;
	}
}

void	possible_character(t_cub3d *info)
{
	int			i;
	int			flag;

	flag = 0;
	i = info->place_map - 1; // needs update (check the placing of the map)
	while (info->map_coord[i])
	{
		if (check_if_player(info->map_coord + i))
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
			return (check_after_finish(info, i));
		i++;
	}
	if (flag == 1)
		info->error = 0;
	else
		info->error = 1;
}

void	ft_check_up_down(t_cub3d *info)
{
	int	i;
	int	j;
	int	lines;

	i = 0;
	lines = calculate_lines(info->ones_zeros);
	while (info->ones_zeros[i])
	{
		j = 0;
		while (info->ones_zeros[i][j])
		{
			if (info->ones_zeros[i][j] == '0'
				|| check_if_player(info->ones_zeros[i] + j))
				return ((void)(info->error = 1));
			j++;
		}
		if (i == lines)
			break ;
		i = lines;
	}
}

void	ft_check_middle(t_cub3d	*info)
{
	int	i;
	int	j;
	int	lines;

	lines = calculate_lines(info->ones_zeros);
	i = 0;
	if (info->ones_zeros[i + 1])
		i++;
	while (info->ones_zeros[i] && i < lines)
	{
		j = 0;
		while (info->ones_zeros[i][j])
		{
			if (j == 0 && (info->ones_zeros[i][j] == '0'
				|| check_if_player(info->ones_zeros[i] + j)
				|| info->ones_zeros[i][ft_strlen(info->ones_zeros[i])] == '0'))
				return ((void)(info->error = 1));
			if (!ft_check_surr(info->ones_zeros, j, i))
				return ((void)(info->error = 1));
			j++;
		}
		i++;
	}
}

void	ft_check_map_borders(t_cub3d	*info)
{
	info->ones_zeros = ft_split (info->map_coord + info->place_map, '\n');
	if (!info->ones_zeros)
		free_in_case(info, 1);
	ft_check_up_down(info);
	ft_check_middle(info);
}
