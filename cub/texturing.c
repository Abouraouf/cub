/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:45:38 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/16 16:21:08 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	floorAndceling(int drawStart, int drawEnd, int x, t_info *i);
double	calc_ray_angle(t_info *i, int x);
t_ray	*cast_ray_dda(double ray_angle, t_info *m);

void calc_text_coor(t_ray *ray, int drawStart, int lineHeight)
{
	double wallX;
	int texX;
	double step;
	double texPos;

	if (ray->side == 0)
		wallX = ray->hitY;
	else
		wallX = ray->hitX;
	wallX -= floor((wallX));
	texX = (int)(wallX * (double)(texWidth));
	if(ray->side == 0 && ray->rayDirX > 0)
		texX = texWidth - texX - 1;
	if(ray->side == 1 && ray->rayDirY < 0)
		texX = texWidth - texX - 1;
	step = 1.0 * texHeight / lineHeight;
	texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
}

int choose_text(t_ray *ray)
{
	int currentTexture;

	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			currentTexture = 0;
		else
			currentTexture = 1;
	}
	else
	{
		if (ray->rayDirY > 0)
			currentTexture = 2;
		else
		currentTexture = 3;
	}
	return (currentTexture);
}

void start_end(t_ray *ray)
{
	ray->lineHeight = (int)(HEIGHT / ray->dist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	if (ray->side == 0)
		ray->texX = ray->hitY;
	else
		ray->texX = ray->hitX;
}

void textures(t_ray *ray, t_info *i, int x, int y)
{
	double step;
	double texPos;
	int currentTexture;
	int texY;
	int color;

	step = 1.0 * texHeight / ray->lineHeight;
	texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * step;
	currentTexture = choose_text(ray);
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		texY = (int)texPos & (texHeight - 1);
		texPos += step;
		color = *(int *)(i->textures[currentTexture].addr + (texY * i->textures[currentTexture].line_length + (int)ray->texX * (i->textures[currentTexture].bits_per_pixel / 8)));
        draw_pixel_on_screen(x, y, color, i);
		y++;
	}
}

int draw_columns(t_info *i)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = NULL;
	while (x < WIDTH)
	{
		if (ray)
			free(ray);
		ray = cast_ray_dda(calc_ray_angle(i, x), i);
		if (!ray)
		{
			x++;
			continue;
		}
		start_end(ray);
		ray->texX -= floor((ray->texX));
		ray->texX = (int)(ray->texX * (double)(texWidth));
		if(ray->side == 0 && ray->rayDirX > 0) ray->texX = texWidth - ray->texX - 1;
		if(ray->side == 1 && ray->rayDirY < 0) ray->texX = texWidth - ray->texX - 1;
		textures(ray, i, x, 0);
		(floorAndceling(ray->drawStart, ray->drawEnd, x, i), x++);
	}
	mlx_put_image_to_window(i->mlx, i->win, i->screen->img_ptr, 0, 0);
	return (free(ray), 0);
}
