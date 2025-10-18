/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:25 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/18 15:35:56 by eabourao         ###   ########.fr       */
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

void	ft_check_if_empty(t_cub3d *info)
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
		if (str[i + 1][j] == ' ' || str[i - 1][j] == ' '
			|| j >= (int)ft_strlen(str[i - 1]))
			return (0);
		if (str[i][j + 1] && ((str[i][j + 1] == ' ')
			|| (str[i][j - 1] == ' ') || j >= (int)ft_strlen(str[i + 1])))
			return (0);
		if (!str[i][j + 1])
			return (0);
		else
			return (1);
	}
	return (1);
}

int	calculate_lines(char **str)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	j = 0;
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j] && flag == 0)
		{
			if (check_if_player(str[i] + j) || str[i][j] == '0'
				|| str[i][j] == '1')
			{
				flag = 1;
				break ;
			}
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
