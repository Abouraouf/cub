/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:02:28 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/19 17:10:09 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	size_t				lenght;
	char				*sub;

	if (!s)
		return (NULL);
	lenght = ft_strlen(s);
	if (start >= lenght)
		return (ft_strdup(""));
	if (lenght - start < len)
		i = lenght - start;
	else
		i = len;
	sub = (char *)malloc (sizeof(char) * i + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, i + 1);
	return (sub);
}

void	ft_read_all(int fd, t_cub3d *info)
{
	char	*tmp;
	char	*tmp_join;

	tmp_join = NULL;
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
