/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:40:08 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/19 17:09:18 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_open_xpm(t_cub3d *info)
{
	int		fd[4];
	int		i;

	i = 0;
	while (info->xpm_files[i])
	{
		fd[i] = open(info->xpm_files[i], O_RDONLY);
		if (fd[i] < 0)
		{
			close(fd[0]);
			close(fd[1]);
			close(fd[2]);
			close(fd[3]);
			info->error = 1;
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}

int	skip_from_end(char *str, int *i)
{
	while (str[(*i)++])
	{
	}
	(*i)--;
	while (*i > 0 && str[(*i)--] == ' ')
	{
	}
	return (*i);
}

int	process_xpm_line(t_cub3d *info, int i, int counter)
{
	int	j;
	int	start;
	int	finish;

	j = 0;
	skip_spaces(info->first_lines[i], &j);
	if (find_nswe(info->first_lines[i] + j, info, j) == 5
		|| find_nswe(info->first_lines[i] + j, info, j) == 6)
	{
		return (1);
	}
	while (info->first_lines[i][j] && info->first_lines[i][j] != ' ')
		j++;
	skip_spaces(info->first_lines[i], &j);
	start = j;
	finish = skip_from_end(info->first_lines[i], &j);
	info->xpm_files[counter] = ft_substr(info->first_lines[i], start, finish);
	return (0);
}

void	extract_xpm_paths(t_cub3d *info)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (counter < 4)
	{
		if (process_xpm_line(info, i, counter) == 0)
		{
			counter++;
		}
		i++;
	}
	info->xpm_files[counter] = NULL;
}

void	trim_xpm(t_cub3d *info)
{
	if (!info->first_lines)
		return ;
	info->xpm_files = malloc(sizeof(char *) * 5);
	extract_xpm_paths(info);
	ft_open_xpm(info);
	order_xpm(info);
	find_player_l(info);
}
