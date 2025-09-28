/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:29:55 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/28 17:49:16 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_cub3d
{
	int		rows;
	char	*map_coord;
	char	*coord;
	char	**first_lines;
	char	**ones_zeros;
	int		error;
	int		files;
	int		place_map;
	int		ceiling;
	int		floor;
}	t_cub3d;

void	ft_read_all(int fd, t_cub3d *info);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	skip_spaces(char *str, int *i);
int		find_nswe(char *str, t_cub3d *info, int i);
int		ft_check_duplicates(int	*flags);
void	possible_character(t_cub3d *info);
void	ft_copy_the_first_lines(t_cub3d *info, int i);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_check_limits_floor(t_cub3d	*info);
void	ft_check_limits_ceiling(t_cub3d	*info);
void	ft_check_map_borders(t_cub3d *info);


#endif