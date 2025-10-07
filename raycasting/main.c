/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:56:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/07 10:52:28 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

t_img *rectangle(void *mlx, int width, int height, int color)
{
	t_img	*new;
	int		x;
	int		y;

	x = 0;
	y = 0;
	new = malloc(sizeof(t_img));
	new->height = height;
	new->width = width;
	new->img_ptr = mlx_new_image(mlx, width, height);
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bits_per_pixel, &new->line_length, &new->endian);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(new, x, y, color);
			x++;
		}
		y++;
	}
	return (new);
}

void draw_2d(t_info *m)
{
	t_img *img;
	t_img *p;
	t_img *ray;

	img = rectangle(m->mlx, 32, 32, 0x00FF0000);
	p = rectangle(m->mlx, 32, 32, 0x0000FF00);
	for (int i = 0; i < m->map_height; i++)
	{
		for (int j = 0; j < m->map_width; j++)
		{
			if (m->map[i][j] == '1')
				mlx_put_image_to_window(m->mlx, m->win, img->img_ptr, j * 32, i * 32);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, p->img_ptr, m->px_px, m->py_px);
	free(img);
	free(p);
}

int frame(void *minimap)
{
	t_info	*m;

	m = minimap;
	mlx_clear_window(m->mlx, m->win);
	usleep(1000);
	draw_2d(m);
	return (0);
}

double dtor(double degree)
{
	return ((M_PI / 180) * degree);
}

int	main(void)
{
	char *map[12] = {
		"111111111111111111111111111111111111",
		"100010000000000000000000000000010001",
		"100010000110010000000000001110000001",
		"100000000000011111000000110001110001",
		"1010000P1111110000011110001110111101",
		"101001001000011110000000011110000001",
		"101001000000011100000000000000000101",
		"101001000000000000000000000000110001",
		"101001000000000000000000000001000011",
		"101001000000011100000000010001000001",
		"101001000000011100000000010000000111",
		"111111111111111111111111111111111111"
	};
	t_info *minimap;

	minimap = malloc(sizeof(t_info));
	minimap->map = map;
	minimap->mlx = mlx_init();
	minimap->win = mlx_new_window(minimap->mlx, WIDTH, HEIGHT, "TITLE");
	minimap->wall_img = rectangle(minimap->mlx, 16, 16, 0x00FF0000);
	minimap->player_img = rectangle(minimap->mlx, 16, 16, 0x0000FF00);
	minimap->px_px = 7 * 32;
	minimap->py_px = 4 * 32;
	minimap->map_height = 12;
	minimap->map_width = 36;
	minimap->pa = dtor(270);
	mlx_loop_hook(minimap->mlx, frame, minimap);
	mlx_key_hook(minimap->win, key_press, minimap);
	mlx_hook(minimap->win, 17, 1L<<0, mlx_close, minimap);
	mlx_loop(minimap->mlx);
	return (0);
}
