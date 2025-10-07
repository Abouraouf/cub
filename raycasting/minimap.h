#ifndef MINIMAP_H
#define MINIMAP_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

# define M_PI	3.14159265358979323846
# define M_PI_2	1.57079632679489661923
#define WIDTH 2000
#define HEIGHT 1500
#define MINIMAP_WIDTH 20
#define MINIMAP_HEIGHT 10
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
	t_img	*wall_img;
	t_img	*player_img;
	t_img	*void_img;
	double	pa;
	double	py_px;
	double	px_px;
	int		map_height;
	int		map_width;
} t_info;

typedef struct {
    double dist;      // perpendicular distance (map units)
    int mapX, mapY;   // the hit cell
    int side;         // 0 vertical, 1 horizontal
    double hitX, hitY; // hit world coords (map units)
} RayHit;

int		mlx_close(t_info *minimap);
int		key_press(int keycode, void *var);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif