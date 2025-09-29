/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:40:08 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/29 14:50:28 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_read_all(int fd, t_cub3d *info)
{
	char	*tmp;
	char	*tmp_join = NULL;

	info->map_coord = NULL;
	info->fd = fd;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		tmp_join = info->map_coord;
		info->map_coord = ft_strjoin(info->map_coord, tmp);
		free(tmp);
		free(tmp_join);
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

