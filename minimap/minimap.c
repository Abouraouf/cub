/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:56:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/09/24 10:48:37 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int mlx_close(t_minimap *minimap);

int key_press(int keycode, void *var)
{
	t_minimap *m;

	m = var;
	if (keycode == 100)
		m->px_px += 4;
	else if (keycode == 97)
		m->px_px -= 4;
	else if (keycode == 119)
		m->py_px -= 4;
	else if (keycode == 115)
		m->py_px += 4;
	else if (keycode == 65307)
		mlx_close(m);
	return (0);
}

int mlx_close(t_minimap *minimap)
{

	mlx_clear_window(minimap->mlx, minimap->win);
	mlx_destroy_window(minimap->mlx, minimap->win);
	mlx_destroy_image(minimap->mlx, minimap->player_img->img_ptr);
	mlx_destroy_image(minimap->mlx, minimap->wall_img->img_ptr);
	mlx_destroy_display(minimap->mlx);
	free(minimap->wall_img);
	free(minimap->player_img);
	free(minimap->mlx);
	free(minimap);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

void draw_minimap(t_minimap *minimap)
{
	int	start_px[2];
	int start_tile[2];
	int	img_coor[2];
	int	i;
	int	j;

	start_px[0] = minimap->px_px - ((MINIMAP_WIDTH * minimap->wall_img->width) / 2);
	start_px[1] = minimap->py_px - ((MINIMAP_HEIGHT * minimap->wall_img->height) / 2);
	start_tile[0] = minimap->px - (MINIMAP_WIDTH / 2);
	start_tile[1] = minimap->py - (MINIMAP_HEIGHT / 2);
	i = 0;
	while (i < MINIMAP_HEIGHT)
	{
		j = 0;
		while (j < MINIMAP_WIDTH)
		{
			if ((i + start_tile[1] < minimap->map_height && j + start_tile[0] < minimap->map_width) && (i + start_tile[1] >= 0 && j + start_tile[0] >= 0) && minimap->map[i + start_tile[1]][j + start_tile[0]] == '1')
			{
				img_coor[0] = ((j + start_tile[0]) * minimap->wall_img->width) - start_px[0];
				img_coor[1] = ((i + start_tile[1]) * minimap->wall_img->height) - start_px[1];
				mlx_put_image_to_window(minimap->mlx, minimap->win, minimap->wall_img->img_ptr, img_coor[0], img_coor[1]);
			}
			j++;
		}
		i++;
	}
}

int frame(void *minimap)
{
	t_minimap	*m;

	m = minimap;
	mlx_clear_window(m->mlx, m->win);
	m->px = m->px_px / 16;
	m->py = m->py_px / 16;
	draw_minimap(minimap);
	mlx_put_image_to_window(m->mlx, m->win, m->player_img->img_ptr, (MINIMAP_WIDTH / 2) * 16, (MINIMAP_HEIGHT / 2) * 16);
	usleep(1000);
	return (0);
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
	t_minimap *minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->map = map;
	minimap->mlx = mlx_init();
	minimap->win = mlx_new_window(minimap->mlx, WIDTH, HEIGHT, "TITLE");
	minimap->wall_img = rectangle(minimap->mlx, 16, 16, 0x00FF0000);
	minimap->player_img = rectangle(minimap->mlx, 16, 16, 0x0000FF00);
	minimap->px = 7;
	minimap->py = 4;
	minimap->px_px = 7 * 16;
	minimap->py_px = 4 * 16;
	minimap->map_height = 12;
	minimap->map_width = 36;
	mlx_loop_hook(minimap->mlx, frame, minimap);
	mlx_key_hook(minimap->win, key_press, minimap);
	mlx_hook(minimap->win, 17, 1L<<0, mlx_close, minimap);
	mlx_loop(minimap->mlx);
	return (0);
}
