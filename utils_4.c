/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:02:28 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/19 17:25:58 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_first_lines(t_cub3d *info)
{
	int	i;
	int	flag[6];
	int	j;

	i = 0;
	j = 0;
	while (j < 6)
	{
		skip_spaces(info->map_coord, &i);
		flag[j] = find_nswe(info->map_coord + i, info, i);
		if (!flag[j++])
			return ((void)(info->error = 1));
		while (info->map_coord[i] && info->map_coord[i] != '\n')
			i++;
		while (info->map_coord[i] && info->map_coord[i] == '\n')
			i++;
	}
	info->place_map = i;
	ft_copy_the_first_lines(info, i);
	if (ft_check_duplicates(flag))
		info->error = 0;
	else
		info->error = 1;
}

void	ft_check_all_above(t_cub3d *info)
{
	ft_check_first_lines(info);
	if (info->error == 1)
		return ;
	possible_character(info);
	if (info->error == 1)
		return ;
	ft_check_limits_floor(info);
	if (info->error == 1)
		return ;
	ft_check_limits_ceiling(info);
	if (info->error == 1)
		return ;
	ft_check_if_empty(info);
	if (info->error == 1)
		return ;
	ft_check_map_borders(info);
	if (info->error == 1)
		return ;
	check_xpm(info, 0);
}

void	ft_check_argv_1(t_cub3d *info, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[--i] == ' ' && i > 0)
	{
	}
	if (ft_strncmp(str + i - 3, ".cub", 4))
		return ((void)(info->error = 1));
	ft_init(info);
	info->error = 0;
}

t_cub3d	*parsing(int ac, char **argv)
{
	t_cub3d	*info;
	int		fd;

	if (ac != 2)
		return (printf("Error\n, wrong argument count\n"), exit(1), NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error\n"), exit(1), NULL);
	info = malloc(sizeof(t_cub3d));
	if (!info)
		free_in_case(info, 1);
	ft_check_argv_1(info, argv[1]);
	if (info->error == 0)
	{
		ft_read_all(fd, info);
		if (!info->map_coord)
			free_in_case(info, 1);
		ft_check_all_above(info);
		if (info->error == 1)
			free_in_case(info, 1);
		trim_xpm(info);
	}
	if (info->error == 1)
		free_in_case(info, 1);
	return (free_in_case(info, 0), info);
}

void	find_player_l(t_cub3d	*info)
{
	int	i;
	int	l;

	i = 0;
	while (info->ones_zeros[i])
	{
		l = 0;
		while (info->ones_zeros[i][l])
		{
			if (check_if_player(info->ones_zeros[i] + l))
			{
				info->player_x = l;
				info->player_y = i;
			}
			l++;
		}
		i++;
	}
	info->rows = i;
}
