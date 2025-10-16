/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:30:47 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/16 11:00:23 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

t_ray *cast_ray_dda(double Px_pixels, double Py_pixels, double ray_angle, t_info *m) {
    double posX = Px_pixels / TILE;
    double posY = Py_pixels / TILE;
    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);
    int mapX = (int)floor(posX);
    int mapY = (int)floor(posY);
    double deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);
    int stepX, stepY;
    double sideDistX, sideDistY;
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
    bool hit = false;
    int side = 0;
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (m->map[mapY][mapX] == '1') hit = true;
    }

	double perpWallDist;
	if (side == 0)
    	perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
	else
    	perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;
    double hitX = posX + rayDirX * perpWallDist;
    double hitY = posY + rayDirY * perpWallDist;

    t_ray *result = malloc(sizeof(t_ray));
    result->dist = perpWallDist;
	result->rayDirX = rayDirX;
	result->rayDirY = rayDirY;
    result->mapX = mapX;
    result->mapY = mapY;
    result->side = side;
    result->hitX = hitX;
    result->hitY = hitY;
    return result;
}

int draw_columns(t_info *i)
{
	for (int x = 0; x < WIDTH; x++) {
        double rayAngle = (i->pa - (FOV / 2)) + (FOV * x / (double)WIDTH);
		if (rayAngle < 0) rayAngle += 2 * M_PI;
		if (rayAngle >= 2 * M_PI) rayAngle -= 2 * M_PI;
		t_ray *ray = cast_ray_dda(i->px_px, i->py_px, rayAngle, i);
		int lineHeight = (int)(HEIGHT / ray->dist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
		int arr[2] = {drawStart, drawEnd};
		double wallX;
		if (ray->side == 0) wallX = ray->hitY;
		else           wallX = ray->hitX;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(texWidth));
		if(ray->side == 0 && ray->rayDirX > 0) texX = texWidth - texX - 1;
		if(ray->side == 1 && ray->rayDirY < 0) texX = texWidth - texX - 1;
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
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
		for(int y = drawStart; y<drawEnd; y++)
      	{
        	int texY = (int)texPos & (texHeight - 1);
        	texPos += step;
        	int color = *(int *)(i->textures[currentTexture].addr + (texY * i->textures[currentTexture].line_length + texX * (i->textures[currentTexture].bits_per_pixel / 8)));
        	if(ray->side == 1) color = (color >> 1) & 8355711;
        	draw_pixel_on_screen(x, y, color, i);
      	}
		for (int ii = 0; ii < drawStart - 1; ii++)
		{
			draw_pixel_on_screen(x, ii, CELING, i);
		}
		for (int ii = drawEnd; ii < HEIGHT; ii++)
		{
			draw_pixel_on_screen(x, ii, FLOOR, i);
		}
	}
	mlx_put_image_to_window(i->mlx, i->win, i->screen->img_ptr, 0, 0);
	return 0;
}
