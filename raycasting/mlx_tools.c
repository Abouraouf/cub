/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:41:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/10 13:50:59 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	draw_column_on_screen(int coor[2], int x, int color, t_info *i)
{
	int	iter;

	iter = coor[0];
	while (iter < coor[1])
	{
		my_mlx_pixel_put(i->screen, x, iter, color);
		iter++;
	}
}

t_img	*screen(void *mlx, int height, int width)
{
	t_img	*new;

	new = malloc(sizeof(t_img));
	new->height = height;
	new->width = width;
	new->img_ptr = mlx_new_image(mlx, width, height);
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bits_per_pixel, &new->line_length, &new->endian);
	return (new);
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

int key_press(int keycode, void *var)
{
	t_info	*m;

	m = var;
	if (keycode == 100) // d
	{
		m->px_px += cos(m->pa + M_PI_2) * 4.0;
		m->py_px += sin(m->pa + M_PI_2) * 4.0;
	}
	else if (keycode == 97) // a
	{
		m->px_px += cos(m->pa + M_PI_2) * -4.0;
		m->py_px += sin(m->pa + M_PI_2) * -4.0;
	}
	if (keycode == 119) // w
	{
		m->px_px = m->px_px + (cos(m->pa) * 4.0);
		m->py_px = m->py_px + (sin(m->pa) * 4.0);
	}
	else if (keycode == 115) // s
	{
		m->px_px = m->px_px + (cos(m->pa) * -4.0);
		m->py_px = m->py_px + (sin(m->pa) * -4.0);
	}
	else if (keycode == 65363) // right
		m->pa += 0.04;
	else if (keycode == 65361) // left
		m->pa += -0.04;
	else if (keycode == 65307)
		mlx_close(m);
	return (0);
}

int mlx_close(t_info *minimap)
{

	mlx_clear_window(minimap->mlx, minimap->win);
	mlx_destroy_window(minimap->mlx, minimap->win);
	//mlx_destroy_image(minimap->mlx, minimap->screen->img_ptr);
	mlx_destroy_display(minimap->mlx);
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
