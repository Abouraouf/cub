/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:59:10 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/19 11:40:36 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_init2(t_ray *result)
{
	if (result->raydirx < 0)
	{
		result->stepx = -1;
		result->sidedistx = (result->posx - result->mapx) * result->deltadistx;
	}
	else
	{
		result->stepx = 1;
		result->sidedistx = (result->mapx + 1.0 - result->posx)
			* result->deltadistx;
	}
	if (result->raydiry < 0)
	{
		result->stepy = -1;
		result->sidedisty = (result->posy - result->mapy) * result->deltadisty;
	}
	else
	{
		result->stepy = 1;
		result->sidedisty = (result->mapy + 1.0 - result->posy)
			* result->deltadisty;
	}
}

void	key_press2(int keycode, t_info *m)
{
	if (keycode == 65363)
		m->pa += 0.08;
	else if (keycode == 65361)
		m->pa += -0.08;
	else if (keycode == 65307)
		mlx_close(m);
}
