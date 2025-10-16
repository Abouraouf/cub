/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:30:47 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/16 14:41:10 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	ray_init(t_ray *result, t_info *m, double ray_angle)
{
	result->posX = m->px_px / TILE;
	result->posY = m->py_px / TILE;
	result->rayDirX = cos(ray_angle);
	result->rayDirY = sin(ray_angle);
	result->mapX = (int)floor(result->posX);
	result->mapY = (int)floor(result->posY);
	result->deltaDistX = (result->rayDirX == 0.0) ? 1e30 : fabs(1.0 / result->rayDirX);
	result->deltaDistY = (result->rayDirY == 0.0) ? 1e30 : fabs(1.0 / result->rayDirY);
	if (result->rayDirX < 0)
	{
		result->stepX = -1;
		result->sideDistX = (result->posX - result->mapX) * result->deltaDistX;
	}
	else
	{
		result->stepX = 1;
		result->sideDistX = (result->mapX + 1.0 - result->posX) * result->deltaDistX;
	}
	if (result->rayDirY < 0)
	{
		result->stepY = -1;
		result->sideDistY = (result->posY - result->mapY) * result->deltaDistY;
	}
	else
	{
		result->stepY = 1;
		result->sideDistY = (result->mapY + 1.0 - result->posY) * result->deltaDistY;
	}
}

void	calc_dist(t_ray *result)
{
	if (result->side == 0)
		result->dist = (result->mapX - result->posX + (1 - result->stepX) / 2.0) / result->rayDirX;
	else
		result->dist = (result->mapY - result->posY + (1 - result->stepY) / 2.0) / result->rayDirY;
	result->hitX = result->posX + result->rayDirX * result->dist;
	result->hitY = result->posY + result->rayDirY * result->dist;
}

t_ray *cast_ray_dda(double ray_angle, t_info *m)
{
	t_ray	*result;

	result = malloc(sizeof(t_ray));
	ray_init(result, m, ray_angle);
	result->side = 0;
	while (1)
	{
		if (result->sideDistX < result->sideDistY)
		{
			result->sideDistX += result->deltaDistX;
			result->mapX += result->stepX;
			result->side = 0;
		}
		else
		{
			result->sideDistY += result->deltaDistY;
			result->mapY += result->stepY;
			result->side = 1;
		}
		if (result->mapY >= m->map_height || result->mapX >= m->map_width || result->mapX < 0 || result->mapY < 0)
			return (free(result), NULL);
		if (m->map[result->mapY][result->mapX] == '1')
			break;
	}
	return (calc_dist(result), result);
}

double	calc_ray_angle(t_info *i, int x)
{
	double rayAngle = (i->pa - (FOV / 2)) + (FOV * x / (double)WIDTH);
	if (rayAngle < 0)
		rayAngle += 2 * M_PI;
	if (rayAngle >= 2 * M_PI)
		rayAngle -= 2 * M_PI;
	return (rayAngle);
}

void floorAndceling(int drawStart, int drawEnd, int x, t_info *i)
{
	int ii;

	ii = 0;
	while (ii < drawStart - 1)
	{
		draw_pixel_on_screen(x, ii, CELING, i);
		ii++;
	}
	ii = drawEnd;
	while (ii < HEIGHT)
	{
		draw_pixel_on_screen(x, ii, FLOOR, i);
		ii++;
	}
}

void calc_text_coor(t_ray *ray, int drawStart, int lineHeight)
{
	double wallX;
	int texX;
	double step;
	double texPos;
	int currentTexture;

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

	ray = NULL;
	for (int x = 0; x < WIDTH; x++)
	{
		if (ray)
			free(ray);
		ray = cast_ray_dda(calc_ray_angle(i, x), i);
		if (!ray)
			continue;
		start_end(ray);
		ray->texX -= floor((ray->texX));
		ray->texX = (int)(ray->texX * (double)(texWidth));
		if(ray->side == 0 && ray->rayDirX > 0) ray->texX = texWidth - ray->texX - 1;
		if(ray->side == 1 && ray->rayDirY < 0) ray->texX = texWidth - ray->texX - 1;
		textures(ray, i, x, 0);
		floorAndceling(ray->drawStart, ray->drawEnd, x, i);
	}
	mlx_put_image_to_window(i->mlx, i->win, i->screen->img_ptr, 0, 0);
	return 0;
}
