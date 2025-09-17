/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:31:09 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/17 16:32:07 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	parse_all(char **arg)
// {
	
// }

int	main(int ac, char **argv)
{
	//parse the second arg and init the info
	t_cub3d	*info;
	int	fd;

	if (ac != 2)
		return (printf("Error\n, wrong argument count\n"), 1);
	open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		
	}
	info = malloc(sizeof(t_cub3d));
	ft_read_all (fd, info);
	if (!info)
		return (printf("Error\n"), 1);
}
