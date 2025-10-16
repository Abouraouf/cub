/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:56:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/16 16:00:23 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	main(int ac, char **argv)
{
	t_cub3d	*p;
	t_info *minimap;

	p = parsing(ac, argv);
	minimap = malloc(sizeof(t_info));
	minimap->distToProjPlane = (WIDTH / 2) / tan(dtor(60) / 2);
	minimap->map = p->ones_zeros;
	minimap->mlx = mlx_init();
	minimap->win = mlx_new_window(minimap->mlx, WIDTH, HEIGHT, "TITLE");
	minimap->px_px = 7 * TILE;
	minimap->py_px = 4 * TILE;
	minimap->floor = p->floor;
	minimap->celing = p->ceiling;
	minimap->map_height = 12;
	minimap->map_width = 36;
	minimap->screen = screen(minimap->mlx, HEIGHT, WIDTH);
	minimap->pa = dtor(270);
	minimap->textures = malloc(sizeof(t_img) * 4);
	minimap->textures[0].img_ptr = mlx_xpm_file_to_image(minimap->mlx, p->xpm_inorder[0], &minimap->textures[0].width, &minimap->textures[0].height);
	minimap->textures[0].addr = mlx_get_data_addr(minimap->textures[0].img_ptr, &minimap->textures[0].bits_per_pixel, &minimap->textures[0].line_length, &minimap->textures[0].endian);
	minimap->textures[1].img_ptr = mlx_xpm_file_to_image(minimap->mlx, p->xpm_inorder[1], &minimap->textures[1].width, &minimap->textures[1].height);
	minimap->textures[1].addr = mlx_get_data_addr(minimap->textures[1].img_ptr, &minimap->textures[1].bits_per_pixel, &minimap->textures[1].line_length, &minimap->textures[1].endian);
	minimap->textures[2].img_ptr = mlx_xpm_file_to_image(minimap->mlx, p->xpm_inorder[2], &minimap->textures[2].width, &minimap->textures[2].height);
	minimap->textures[2].addr = mlx_get_data_addr(minimap->textures[2].img_ptr, &minimap->textures[2].bits_per_pixel, &minimap->textures[2].line_length, &minimap->textures[2].endian);
	minimap->textures[3].img_ptr = mlx_xpm_file_to_image(minimap->mlx, p->xpm_inorder[3], &minimap->textures[3].width, &minimap->textures[3].height);
	minimap->textures[3].addr = mlx_get_data_addr(minimap->textures[3].img_ptr, &minimap->textures[3].bits_per_pixel, &minimap->textures[3].line_length, &minimap->textures[3].endian);
	mlx_loop_hook(minimap->mlx, frame, minimap);
	mlx_key_hook(minimap->win, key_press, minimap);
	mlx_hook(minimap->win, 17, 1L<<0, mlx_close, minimap);
	mlx_loop(minimap->mlx);
	return (0);
}
