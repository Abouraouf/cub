/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:30:47 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/17 11:34:32 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_init2(t_ray *result);

void	ray_init(t_ray *result, t_info *m, double ray_angle)
{
	result->side = 0;
	result->posX = m->px_px / TILE;
	result->posY = m->py_px / TILE;
	result->rayDirX = cos(ray_angle);
	result->rayDirY = sin(ray_angle);
	result->mapX = (int)floor(result->posX);
	result->mapY = (int)floor(result->posY);
	result->deltaDistX = (result->rayDirX == 0.0) ? 1e30 : fabs(1.0 / result->rayDirX);
	result->deltaDistY = (result->rayDirY == 0.0) ? 1e30 : fabs(1.0 / result->rayDirY);
	ray_init2(result);
}

void	calc_dist(t_ray *result)
{
	if (result->side == 0)
		result->dist = (result->mapX - result->posX + ((1 - result->stepX) / 2.0)) / result->rayDirX;
	else
		result->dist = (result->mapY - result->posY + ((1 - result->stepY) / 2.0)) / result->rayDirY;
	result->hitX = result->posX + result->rayDirX * result->dist;
	result->hitY = result->posY + result->rayDirY * result->dist;
}

t_ray *cast_ray_dda(double ray_angle, t_info *m)
{
	t_ray	*result;

	result = malloc(sizeof(t_ray));
	ray_init(result, m, ray_angle);
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
		if (result->mapY >= m->map_height || result->mapY < 0 || result->mapX >= (int)ft_strlen(m->map[result->mapY])
				|| result->mapX < 0)
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
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd < 0)
		drawEnd = 0;
	while (ii < drawStart - 1)
	{
		draw_pixel_on_screen(x, ii, i->celing, i);
		ii++;
	}
	ii = drawEnd;
	while (ii < HEIGHT)
	{
		draw_pixel_on_screen(x, ii, i->floor, i);
		ii++;
	}
}
