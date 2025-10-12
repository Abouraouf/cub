/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:56:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/10 17:07:39 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int frame(void *minimap)
{
	t_info	*m;
	int		i;

	i = 0;
	m = minimap;
	while (i < WIDTH * HEIGHT * (m->screen->bits_per_pixel / 8))
	{
		m->screen->addr[i] = 0;
		i++;
	}
	draw_columns(m);
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
	minimap->distToProjPlane = (WIDTH / 2) / tan(dtor(60) / 2);
	minimap->map = map;
	minimap->mlx = mlx_init();
	minimap->win = mlx_new_window(minimap->mlx, WIDTH, HEIGHT, "TITLE");
	minimap->px_px = 7 * TILE;
	minimap->py_px = 4 * TILE;
	minimap->map_height = 12;
	minimap->map_width = 36;
	minimap->screen = screen(minimap->mlx, HEIGHT, WIDTH);
	minimap->pa = dtor(270);
	mlx_loop_hook(minimap->mlx, frame, minimap);
	mlx_key_hook(minimap->win, key_press, minimap);
	mlx_hook(minimap->win, 17, 1L<<0, mlx_close, minimap);
	mlx_loop(minimap->mlx);
	return (0);
}
