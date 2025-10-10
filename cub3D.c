/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/10 14:17:01 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_init(t_cub3d *info)
{
	info->coord = NULL;
	info->first_lines = NULL;
	info->ones_zeros = NULL;
	info->map_coord = NULL;
}

int	check_end_xpm(char *str)
{
	if (!ft_strncmp(str, ".xpm", 4))
		return (1);
	return (0);
}

void		check_xpm(t_cub3d *info)
{
	int i;
	int j;

	i = 0;
	while (info->first_lines[i] && i < 4)
	{
		j = 0;
				
		if ((int)ft_strlen(info->first_lines[i]) > 4)
		{
			while (info->first_lines[i][j])
				j++;
			while (info->first_lines[i][--j] == ' ')
			{}
			j++;
			if (!check_end_xpm(info->first_lines[i] + j - 4))
				return ((void)(info->error = 1));
		}
		else
			return ((void)(info->error = 1));
		i++;
	}
}

void	free_in_case(t_cub3d *info, int i) // if 0 free everything and close file descriptors if 1 free useless
{
	if (i == 0)
	{
		free(info->coord);
		info->coord = NULL;
		free(info->map_coord);
		info->map_coord = NULL;
		if (info->fd >= 0)
			close(info->fd);
		exit(0);
	}
	
	if (i == 1)
	{
		ft_free(info->first_lines);
		info->first_lines= NULL;
		ft_free(info->ones_zeros);
		info->ones_zeros = NULL;
		free(info->coord);
		info->coord = NULL;
		free(info->map_coord);
		info->map_coord = NULL;
		if (info->fd >= 0)
			close(info->fd);
		free(info);
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
	ft_check_limits_ceiling(info); //handle the exit if anything happens
	if (info->error == 1)
		return ;
	ft_check_if_empty(info);
	if (info->error == 1)
		return ;
	ft_check_map_borders(info);
	if (info->error == 1)
		return ;
	check_xpm(info);

}

void	ft_check_argv_1(t_cub3d *info, char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	
	while (str[--i] == ' ' && i > 0)
	{}
	if (ft_strncmp(str + i - 3, ".cub", 4))
		return ((void)(info->error = 1));
	info->error = 0;
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
		free_in_case(info, 1);
	ft_check_argv_1(info, argv[1]);
	ft_init(info);
	if (info->error == 0)
	{
		ft_read_all(fd, info);
		if (!info->map_coord)
			free_in_case(info, 1);
		ft_check_all_above(info);
	}
	if (info->error == 1)
		free_in_case(info, 1);
	free_in_case(info, 0);
}
 