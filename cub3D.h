/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:29:55 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/13 16:12:33 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "get_next_line.h"

typedef struct s_data {
    void *mlx;
    void *win;
    int frame; // frame counter
    // other data like image pointers, coordinates etc.
} t_data;

typedef struct s_cub3d
{
	char	**first_lines;
	char	**xpm_files;
	char	**ones_zeros;
	int		fd;
	int		rows;
	char	*map_coord;
	char	*coord;
	int		error;
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
void	ft_check_if_empty(t_cub3d *info);
void	ft_free(char **str);
void	free_in_case(t_cub3d *info, int i);
void	trim_xpm(t_cub3d *info);
char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif