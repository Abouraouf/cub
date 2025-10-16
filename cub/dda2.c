/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:59:10 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/16 15:56:42 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_init2(t_ray *result)
{
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
