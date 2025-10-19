/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/19 17:26:15 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init(t_cub3d *info)
{
	info->coord = NULL;
	info->xpm_files = NULL;
	info->first_lines = NULL;
	info->ones_zeros = NULL;
	info->map_coord = NULL;
	info->xpm_inorder = NULL;
}

int	check_end_xpm(char *str)
{
	if (!ft_strncmp(str, ".xpm", 4))
		return (1);
	return (0);
}

void	check_xpm(t_cub3d *info, int i)
{
	int	j;

	while (info->first_lines[i])
	{
		j = 0;
		if ((int)ft_strlen(info->first_lines[i]) > 4)
		{
			skip_spaces(info->first_lines[i], &j);
			if (find_nswe(info->first_lines[i] + j, info, j) == 5
				|| find_nswe(info->first_lines[i] + j, info, j) == 6)
			{
				i++;
				continue ;
			}
			while (info->first_lines[i][j])
				j++;
			while (info->first_lines[i][--j] == ' ')
				;
			if (!check_end_xpm(info->first_lines[i] + j - 3))
				return ((void)(info->error = 1));
		}
		else
			return ((void)(info->error = 1));
		i++;
	}
}

void	free_in_case(t_cub3d *info, int i)
{
	if (i == 0)
	{
		free(info->coord);
		info->coord = NULL;
		free(info->map_coord);
		info->map_coord = NULL;
		if (info->fd >= 0)
			close(info->fd);
	}
	if (i > 0)
	{
		free(info->xpm_inorder);
		ft_free(info->first_lines);
		info->first_lines = NULL;
		info->ones_zeros = NULL;
		ft_free(info->xpm_files);
		info->xpm_files = NULL;
		free(info->coord);
		info->coord = NULL;
		free(info->map_coord);
		info->map_coord = NULL;
		free(info);
		if (i == 1)
			return (printf("Error\n"), exit(1));
	}
}

void	ft_copy_the_first_lines(t_cub3d *info, int i)
{
	int	j;

	j = -1;
	info->coord = malloc(i + 1);
	if (!info->coord)
		free_in_case(info, 1);
	while (++j < i)
		info->coord[j] = info->map_coord[j];
	info->coord[j] = '\0';
	info->first_lines = ft_split(info->coord, '\n');
	if (!info->first_lines)
		free_in_case(info, 1);
}
