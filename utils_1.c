/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:40:08 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/25 15:16:56 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// char	**reading(char *name_of_file)
// {
// 	int		fd;
// 	char	**ret;
// 	int		i;

// 	fd = open(name_of_file, O_RDONLY);
// 	i = 0;

// 	if (fd < 0)
// 	{
// 		printf("Error\n");
// 		exit(1);
// 	}
// 	while (1)
// 	{

// 	}
// }

void	ft_read_all(int fd, t_cub3d *info)
{
	char	*tmp;

	info->map_coord = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		info->map_coord = ft_strjoin(info->map_coord, tmp);
		free(tmp);
		tmp = NULL;
	}
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

