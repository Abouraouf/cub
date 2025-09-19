/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/17 18:29:26 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_nswe(char *str)
{
	if (ft_strncmp(str, "NO", 2) || ft_strncmp(str, "SO", 2)
		|| ft_strncmp(str, "WE", 2) || ft_strncmp(str, "EA", 2));
		return (1);
	return (0);
}

void	ft_take_coord(t_cub3d *info)
{
	int	i;
	int	j;
	int flag;

	flag = 0;
	j = 0;
	i = 0;
	while (info->map_coord[i])
	{
		while (info->map_coord[j])
		{
			if ()
				
			else
				j++;
		}
		
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
	info->headings = NULL;
}
