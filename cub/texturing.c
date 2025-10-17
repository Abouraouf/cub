/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:45:38 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/17 20:05:21 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	floorandceling(int drawstart, int drawend, int x, t_info *i);
double	calc_ray_angle(t_info *i, int x);
t_ray	*cast_ray_dda(double ray_angle, t_info *m);

void	calc_text_coor(t_ray *ray, int drawstart, int lineheight)
{
	double	wallx;
	int		texx;
	double	step;
	double	texpos;

	if (ray->side == 0)
		wallx = ray->hity;
	else
		wallx = ray->hitx;
	wallx -= floor((wallx));
	texx = (int)(wallx * (double)(TEXWIDTH));
	if (ray->side == 0 && ray->raydirx > 0)
		texx = TEXWIDTH - texx - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		texx = TEXWIDTH - texx - 1;
	step = 1.0 * TEXHEIGHT / lineheight;
	texpos = (drawstart - HEIGHT / 2 + lineheight / 2) * step;
}

int	choose_text(t_ray *ray)
{
	int	currenttexture;

	if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			currenttexture = 0;
		else
			currenttexture = 1;
	}
	else
	{
		if (ray->raydiry > 0)
			currenttexture = 2;
		else
			currenttexture = 3;
	}
	return (currenttexture);
}

void	start_end(t_ray *ray)
{
	ray->lineheight = (int)(HEIGHT / ray->dist);
	ray->drawstart = -ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawend >= HEIGHT)
		ray->drawend = HEIGHT - 1;
	if (ray->side == 0)
		ray->texx = ray->hity;
	else
		ray->texx = ray->hitx;
}

void	textures(t_ray *ray, t_info *i, int x, int y)
{
	double	step;
	double	texpos;
	int		currenttexture;
	int		texy;
	int		color;

	step = 1.0 * TEXHEIGHT / ray->lineheight;
	texpos = (ray->drawstart - HEIGHT / 2 + ray->lineheight / 2) * step;
	currenttexture = choose_text(ray);
	y = ray->drawstart;
	while (y < ray->drawend)
	{
		texy = (int)texpos & (TEXHEIGHT - 1);
		texpos += step;
		color = *(int *)(i->textures[currenttexture].addr
				+ (texy * i->textures[currenttexture].line_length
					+ (int)ray->texx
					* (i->textures[currenttexture].bits_per_pixel / 8)));
		my_mlx_pixel_put(i->screen, x, y, color);
		y++;
	}
}

int	draw_columns(t_info *i)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = NULL;
	while (x < WIDTH)
	{
		(free(ray), ray = cast_ray_dda(calc_ray_angle(i, x), i));
		if (!ray)
		{
			x++;
			continue ;
		}
		start_end(ray);
		ray->texx -= floor((ray->texx));
		ray->texx = (int)(ray->texx * (double)(TEXWIDTH));
		if (ray->side == 0 && ray->raydirx > 0)
			ray->texx = TEXWIDTH - ray->texx - 1;
		if (ray->side == 1 && ray->raydiry < 0)
			ray->texx = TEXWIDTH - ray->texx - 1;
		textures(ray, i, x, 0);
		(floorandceling(ray->drawstart, ray->drawend, x, i), x++);
	}
	mlx_put_image_to_window(i->mlx, i->win, i->screen->img_ptr, 0, 0);
	return (free(ray), 0);
}
