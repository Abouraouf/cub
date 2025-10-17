/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:29:55 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/17 09:48:14 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
#include "get_next_line.h"

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define WIDTH 2000
#define HEIGHT 1500
#define FOV (M_PI / 3.0)
#define TILE 64
#define texWidth 64
#define texHeight 64
#define	CELING 0x0086C1B9
#define	FLOOR 0x00555555

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
} t_img;

typedef struct s_info
{
	char	**map;
	void	*mlx;
	void	*win;
	t_img	*screen;
	t_img	*textures;
	double	pa;
	double	py_px;
	double	px_px;
	int		map_height;
	int		map_width;
	double	distToProjPlane;
	int		floor;
	int		celing;
} t_info;

typedef struct s_ray{
	int		mapX, mapY;
    int		side;
	int		stepX, stepY;
	int		lineHeight;
	int		drawEnd;
	int		drawStart;
    double	dist;
    double	hitX, hitY;
	double	rayDirX;
	double	rayDirY;
	double	posX, posY;
	double	deltaDistX, deltaDistY;
	double	sideDistX, sideDistY;
	double	texX;
} t_ray;

typedef struct s_cub3d
{
	char	**first_lines;
	char	**xpm_files;
	char	**xpm_inorder;
	char	**ones_zeros;
	int		ceiling_for_mlx;
	int		floor_for_mlx;
	int		fd;
	int		rows;
	char	*map_coord;
	char	*coord;
	int		player_x;
	int		player_y;
	int		error;
	int		place_map;
	int		ceiling;
	int		floor;
}	t_cub3d;

void	draw_pixel_on_screen(int x, int y, int color, t_info *i);
void	draw_column_on_screen(int coor[2], int x, int color, t_info *i);
t_img	*screen(void *mlx, int height, int width);
int		draw_columns(t_info *i);
double	dtor(double degree);
int		mlx_close(t_info *minimap);
int		key_press(int keycode, void *var);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
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
void	order_xpm(t_cub3d *info);
t_cub3d	*parsing(int ac, char **argv);
int		check_if_player(char *str);
void	find_player_l(t_cub3d	*info);

#endif