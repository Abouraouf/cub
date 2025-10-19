/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:02:28 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/18 15:39:46 by eabourao         ###   ########.fr       */
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_src;
	size_t	i;

	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (size_src);
}
