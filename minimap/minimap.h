#ifndef MINIMAP_H
#define MINIMAP_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 2000
#define HEIGHT 1500
#define MINIMAP_WIDTH 20
#define MINIMAP_HEIGHT 10

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

typedef struct s_minimap
{
	char	**map;
	void	*mlx;
	void	*win;
	t_img	*wall_img;
	t_img	*player_img;
	t_img	*void_img;
	int		py;
	int		px;
	int		py_px;
	int		px_px;
	int		map_height;
	int		map_width;
} t_minimap;


#endif