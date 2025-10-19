/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:30:47 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/19 13:57:03 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_init2(t_ray *result);

t_ray	*ray_init(t_info *m, double ray_angle)
{
	t_ray	*result;

	result = malloc(sizeof(t_ray));
	if (!result)
		mlx_close(m);
	result->side = 0;
	result->posx = m->px_px / TILE;
	result->posy = m->py_px / TILE;
	result->raydirx = cos(ray_angle);
	result->raydiry = sin(ray_angle);
	result->mapx = (int)floor(result->posx);
	result->mapy = (int)floor(result->posy);
	if (result->raydirx == 0.0)
		result->deltadistx = 1e30;
	else
		result->deltadistx = fabs(1.0 / result->raydirx);
	if (result->raydiry == 0.0)
		result->deltadisty = 1e30;
	else
		result->deltadisty = fabs(1.0 / result->raydiry);
	ray_init2(result);
	return (result);
}

void	calc_dist(t_ray *result)
{
	if (result->side == 0)
		result->dist = (result->mapx - result->posx
				+ ((1 - result->stepx) / 2.0)) / result->raydirx;
	else
		result->dist = (result->mapy - result->posy
				+ ((1 - result->stepy) / 2.0)) / result->raydiry;
	result->hitx = result->posx + result->raydirx * result->dist;
	result->hity = result->posy + result->raydiry * result->dist;
}

t_ray	*cast_ray_dda(double ray_angle, t_info *m)
{
	t_ray	*result;

	result = ray_init(m, ray_angle);
	while (1)
	{
		if (result->sidedistx < result->sidedisty)
		{
			result->sidedistx += result->deltadistx;
			result->mapx += result->stepx;
			result->side = 0;
		}
		else
		{
			result->sidedisty += result->deltadisty;
			result->mapy += result->stepy;
			result->side = 1;
		}
		if (result->mapy >= m->map_height || result->mapy < 0
			|| result->mapx >= (int)ft_strlen(m->map[result->mapy])
			|| result->mapx < 0)
			return (free(result), NULL);
		if (m->map[result->mapy][result->mapx] == '1')
			break ;
	}
	return (calc_dist(result), result);
}

double	calc_ray_angle(t_info *i, int x)
{
	double	rayangle;

	rayangle = (i->pa - (FOV / 2)) + (FOV * x / (double)WIDTH);
	if (rayangle < 0)
		rayangle += 2 * M_PI;
	if (rayangle >= 2 * M_PI)
		rayangle -= 2 * M_PI;
	return (rayangle);
}

void	floorandceling(int drawstart, int drawend, int x, t_info *i)
{
	int	ii;

	ii = 0;
	if (drawstart < 0)
		drawstart = 0;
	if (drawend < 0)
		drawend = 0;
	while (ii < drawstart - 1)
	{
		my_mlx_pixel_put(i->screen, x, ii, i->celing);
		ii++;
	}
	ii = drawend;
	while (ii < HEIGHT - 1)
	{
		my_mlx_pixel_put(i->screen, x, ii, i->floor);
		ii++;
	}
}
