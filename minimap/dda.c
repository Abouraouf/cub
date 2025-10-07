/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:30:47 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/10/06 16:36:09 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

RayHit cast_ray_dda(double Px_pixels, double Py_pixels, double ray_angle, t_info *m) {
    // Convert player pos to map units (cells)
    double posX = Px_pixels / TILE;
    double posY = Py_pixels / TILE;

    // Direction vector (unit)
    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);

    // Current map square
    int mapX = (int)floor(posX);
    int mapY = (int)floor(posY);

    // Avoid division by zero (parallel rays)
    double deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);

    int stepX, stepY;
    double sideDistX, sideDistY;

    // Compute step and initial sideDist
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

    // DDA loop
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
        if (m->map[mapY][mapX] > 0) hit = true;
    }

    // Compute perpendicular distance to the wall (map units)
    double perpDist;
    if (side == 0) {
        perpDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    } else {
        perpDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;
    }

    // compute world hit coordinates (map units)
    double hitX = posX + rayDirX * perpDist;
    double hitY = posY + rayDirY * perpDist;

    RayHit result;
    result.dist = perpDist;      // in map units; multiply by TILE to get pixels
    result.mapX = mapX;
    result.mapY = mapY;
    result.side = side;
    result.hitX = hitX;
    result.hitY = hitY;
    return result;
}
