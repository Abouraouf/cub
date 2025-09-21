/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/21 15:35:37 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_nswe(char *str)
{
	if (ft_strncmp(str, "NO", 2))
		return (1);
	if (ft_strncmp(str, "SO", 2))
		return (2);
	if (ft_strncmp(str, "WE", 2))
		return (3);
	if (ft_strncmp(str, "EA", 2))
		return (4);
	if (ft_strncmp(str, "F", 2))
		return (5);
	return (0);
}

void	trim_spaces(char *str)
{
	if (!str)
		return ;
	while (*str && *str == ' ')
		str++;
}

// this one checks the first line
int	ft_check_first_lines(t_cub3d	*info)
{
	int	i;
	int	ret;

	ret = find_nswe(info->coord[i]);
	i = 0;
	while (info->coord[i])
	{
		if (!ret)
			return (ret);
	}
}

char	*ft_read_first_lines(t_cub3d *info)
{
	int	one;
	int	i;

	i = 0;
	while (info->coord[i])
	{
		trim_spaces(info->coord + i);
		while (info->coord[i] && info->coord[i] != '\n')
		{
			
		}
		
	}
	
}

int	ft_check_first_lines_character(t_cub3d	*info)
{
	
}

int	ft_check_first_lines_files(t_cub3d	*info)
{
	
}

void	ft_take_coord(t_cub3d *info)
{
	int	i;
	int	j;
	int	flag;

	if (!ft_check_first_lines(info) || !ft_check_first_lines_character(info)
		|| !ft_check_first_lines(info))
		return (NULL);
	flag = 0;
	j = 0;
	i = 0;
	while (info->map_coord[i])
	{
		if ()
	}
}

int	parse_all(int fd, t_cub3d *info)
{
	ft_read_all (fd, info);
	ft_take_coord(info);
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
	info = malloc(sizeof(t_cub3d));
	if (!info)
	{
		close(fd); 
		return (printf("Error\n"), 1);
	}
	info->error = 0;
	info->coord = NULL;
	info->map_coord = NULL;
}
