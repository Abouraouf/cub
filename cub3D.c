/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/29 10:51:37 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_copy_the_first_lines(t_cub3d *info, int i)
{
	int	j;

	j = -1;
	info->coord = malloc(i + 1);
	if (!info->coord)
		return ;// memory
	while (++j < i)
	{
		info->coord[j] = info->map_coord[j];
	}
	info->coord[j] = '\0';
	info->first_lines = ft_split(info->coord, '\n');
}


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
	possible_character(info);
	ft_check_limits_floor(info);
	ft_check_limits_ceiling(info); //handle the exit if anything happens
	ft_check_map_borders(info);
}

int	main(int ac, char **argv)
{
	t_cub3d	*info; //parse the second arg and init the info
	int		fd;

	if (ac != 2)
		return (printf("Error\n, wrong argument count\n"), 1);

	fd = open(argv[1], O_RDONLY);

	if (fd < 0)
		return (printf("Error\n"), 1);
	info = malloc(sizeof(t_cub3d)); //
	if (!info)
	{
		close(fd);
		return (printf("Error\n"), 1);
	}
	ft_read_all(fd, info);
	if (!info->map_coord)
		return 1; //free and the other shyyt
	ft_check_all_above(info);
	for (size_t i = 0; info->first_lines[i]; i++)
	{
		printf("%s\n", info->first_lines[i]);
	}
	
}
 