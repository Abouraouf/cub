#ifndef MINIMAP_H
#define MINIMAP_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define WIDTH 2000
#define HEIGHT 1500
#define FOV (M_PI / 3.0)
#define TILE 32

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
	double	pa;
	double	py_px;
	double	px_px;
	int		map_height;
	int		map_width;
	double	distToProjPlane;
} t_info;

typedef struct s_ray{
    double dist;
    int mapX, mapY;
    int side;
    double hitX, hitY;
} t_ray;

void	draw_column_on_screen(int coor[2], int x, int color, t_info *i);
t_img	*rectangle(void *mlx, int width, int height, int color);
t_img	*screen(void *mlx, int height, int width);
int		draw_columns(t_info *i);
double	dtor(double degree);
int		mlx_close(t_info *minimap);
int		key_press(int keycode, void *var);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif