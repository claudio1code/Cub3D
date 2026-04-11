/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:05:00 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ray_x(t_win *lmx, float *ra, float ratan)
{
	lmx->hx = lmx->px;
	lmx->hy = lmx->py;
	if (*ra < 0.001 || fabs(*ra - PI) < 0.001)
		return ;
	ratan = -1 / tan(*ra);
	lmx->atan = ratan;
	if (lmx->atan > 100)
		lmx->atan = 100;
	if (lmx->atan < -100)
		lmx->atan = -100;
	if (*ra > PI)
	{
		lmx->ry = (((int)lmx->py >> 6) << 6) - 0.0001;
		lmx->rx = (lmx->py - lmx->ry) * ratan + lmx->px;
		lmx->yo = -64;
		lmx->xo = -lmx->yo * ratan;
	}
	else if (*ra < PI)
	{
		lmx->ry = (((int)lmx->py >> 6) << 6) + 64 + 0.0001;
		lmx->rx = (lmx->py - lmx->ry) * ratan + lmx->px;
		lmx->yo = 64;
		lmx->xo = -lmx->yo * ratan;
	}
}

static void	ray_y(t_win *lmx, float *ra, float ratan)
{
	ratan = tan(*ra);
	lmx->atan = ratan;
	if (lmx->atan > 100)
		lmx->atan = 100;
	if (lmx->atan < -100)
		lmx->atan = -100;
	lmx->d_v = 1000000;
	lmx->vx = lmx->px;
	lmx->vy = lmx->py;
	if (*ra > PI / 2 && *ra < 3 * PI / 2)
	{
		lmx->rx = (((int)lmx->px >> 6) << 6) - 0.0001;
		lmx->ry = (lmx->rx - lmx->px) * ratan + lmx->py;
		lmx->xo = -64;
		lmx->yo = lmx->xo * ratan;
	}
	else if (*ra < PI / 2 || *ra > 3 * PI / 2)
	{
		lmx->rx = (((int)lmx->px >> 6) << 6) + 64 + 0.0001;
		lmx->ry = (lmx->rx - lmx->px) * ratan + lmx->py;
		lmx->xo = 64;
		lmx->yo = lmx->xo * ratan;
	}
}

static void	ray_step(t_win *lmx, float *dist_v, float *hit_x, float *hit_y)
{
	while (1)
	{
		if ((int)lmx->ry >> 6 >= lmx->map_data->height
			|| (int)lmx->rx >> 6 >= lmx->map_data->width
			|| (int)lmx->rx >> 6 < 0 || (int)lmx->ry >> 6 < 0)
			break ;
		if (lmx->matrix[(int)lmx->ry >> 6][(int)lmx->rx >> 6] == 1)
		{
			*dist_v = dist(lmx->px, lmx->py, lmx->rx, lmx->ry);
			*hit_x = lmx->rx;
			*hit_y = lmx->ry;
			break ;
		}
		else
		{
			lmx->rx += lmx->xo;
			lmx->ry += lmx->yo;
		}
	}
}

static void	draw_ray(t_win *lmx, float ra, int c)
{
	float	wall_x;
	int		side;

	if (lmx->d_v >= 1000000 && lmx->d_h >= 1000000)
		return ;
	if (lmx->d_v < lmx->d_h)
	{
		lmx->d_t = dist(lmx->px, lmx->py, lmx->vx, lmx->vy) * cos(ra - lmx->pa);
		side = 2 + (ra < PI / 2 || ra > 3 * PI / 2);
		wall_x = fmod(lmx->vy, 64) / 64.0f;
	}
	else
	{
		lmx->d_t = dist(lmx->px, lmx->py, lmx->hx, lmx->hy) * cos(ra - lmx->pa);
		side = (ra < PI);
		wall_x = fmod(lmx->hx, 64) / 64.0f;
	}
	draw_line(lmx, c, (int)(wall_x * lmx->tex[side].width), &lmx->tex[side]);
}

void	rays(t_win *lmx, int r, float ra, float ratan)
{
	int		c;

	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	c = -1;
	while (++c < r)
	{
		lmx->d_h = 1000000;
		ray_x(lmx, &ra, ratan);
		ray_step(lmx, &lmx->d_h, &lmx->hx, &lmx->hy);
		ray_y(lmx, &ra, ratan);
		ray_step(lmx, &lmx->d_v, &lmx->vx, &lmx->vy);
		draw_ray(lmx, ra, c);
		ra += (60 * DR) / 1920;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}
