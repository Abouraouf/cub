/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/24 12:56:01 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this one checks the first line
// int	ft_check_first_lines(t_cub3d	*info)
// {
// 	int	i;
// 	int	ret;

// 	ret = find_nswe(info->coord[i]);
// 	i = 0;
// 	while (info->coord[i])
// 	{
// 		if (!ret)
// 			return (ret);
// 	}
// }

void	ft_copy_the_first_lines(t_cub3d *info, int i)
{
	int	j;

	j = -1;
	info->map_coord = malloc(i + 1);
	if (!info->map_coord)
		return ;// memory
	while (++j < i)
	{
		info->map_coord[j] = info->coord[j];
	}
	info->map_coord[j] = '\0';
}

int	ft_check_first_lines(t_cub3d *info)
{
	int	i;
	int	flag[5];
	int	j;

	i = 0;
	j = 0;
	while (j < 5)
	{
		skip_spaces(info->coord, &i);
		flag[j] = find_nswe(info->coord + i);
		if (!flag[j++])
			return (info->error = 1, 0); 
		while (info->coord[i] && info->coord[i] != '\n')
			i++;
		while (info->coord[i] && info->coord[i] == '\n')
			i++;
	}
	ft_copy_the_first_lines(info, i); 
	return (ft_check_duplicates(flag));
}

// int	ft_check_first_lines_character(t_cub3d	*info)
// {
	
// }

// int	ft_check_first_lines_files(t_cub3d	*info)
// {
	
// }

// void	ft_take_coord(t_cub3d *info)
// {
// 	int	i;
// 	int	j;
// 	int	flag;

// 	flag = 0;
// 	j = 0;
// 	i = 0;
// 	// if (!ft_check_first_lines(info) || !ft_check_first_lines_character(info)
// 	// 	|| !ft_check_first_lines_files(info))
// 	// 	return (info->error = 1);
// 	// while (info->map_coord[i])
// 	// {
// 	// 	if ()
// 	// }
// }

// int	parse_all(int fd, t_cub3d *info)
// {
// 	ft_read_all (fd, info);
// 	ft_take_coord(info);
// }

int	main(int ac, char **argv)
{
	(void) ac, (void) argv;
	char *check = "NO 1 \n SO 2 \n WE 3 \n EA 4 \n F 5";
	
	t_cub3d	*info; //parse the second arg and init the info
	// int		fd;

	// if (ac != 2)
	// 	return (printf("Error\n, wrong argument count\n"), 1);

	// fd = open(argv[1], O_RDONLY);

	// if (fd < 0)
	// 	return (printf("Error\n"), 1);
	info = malloc(sizeof(t_cub3d));
	info->coord = check;
	// if (!info)
	// {
	// 	close(fd); 
	// 	return (printf("Error\n"), 1);
	// }
	// info->error = 0;
	// info->coord = NULL;
	// info->map_coord = NULL;
	printf("%d\n", ft_check_first_lines(info));
	printf("%s\n", info->map_coord);
}
