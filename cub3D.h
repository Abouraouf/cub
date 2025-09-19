/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:29:55 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/17 18:25:38 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"


typedef enum e_coord
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
}			t_coord;


typedef struct s_cub3d
{
	int		rows;
	char	*map_coord;
	char	*coord;
	int		error;
	t_coord	*nswe;
}	t_cub3d;
void	ft_read_all(int fd, t_cub3d *info);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif