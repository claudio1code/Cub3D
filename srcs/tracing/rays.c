/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:23:48 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 09:51:36 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	draw_line(t_win *lmx, int x, int tex_x, t_tex *tex)
{
	int		y;
	int		start;
	float	tex_pos;
	char	*dst;
	char	*src;

	if (lmx->d_t < 0.1)
		lmx->d_t = 0.1;
	lmx->l_h = (64 * 1024) / lmx->d_t;
	if (lmx->l_h > 1024)
		lmx->l_h = 1024;
	start = (1024 / 2) - (lmx->l_h / 2);
	if (start < 0)
		start = 0;
	tex_pos = (start - (1024 / 2) + ((64 * 1024) / lmx->d_t) / 2)
		* (float)tex->height / ((64 * 1024) / lmx->d_t);
	y = -1;
	while (++y < lmx->l_h && (y + start) < 1024)
	{
		tex_pos += (float)tex->height / ((64 * 1024) / lmx->d_t);
		src = tex->addr + (((int)tex_pos % tex->height)
				* tex->ll + tex_x * (tex->bpp / 8));
		dst = lmx->addr + ((y + start) * lmx->ll + x * (lmx->bpp / 8));
		*(unsigned int *)dst = *(unsigned int *)src;
	}
}

static void	ray_x(t_win*lmx, float*ra, float ratan)
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
	if (*ra < PI)
	{
		lmx->ry = (((int)lmx->py >> 6) << 6) + 64 + 0.0001;
		lmx->rx = (lmx->py - lmx->ry) * ratan + lmx->px;
		lmx->yo = 64;
		lmx->xo = -lmx->yo * ratan;
	}
	ray_x2(lmx);
}

static void	ray_y(t_win*lmx, float*ra, float ratan)
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
	if (*ra < PI / 2 || *ra > 3 * PI / 2)
	{
		lmx->rx = (((int)lmx->px >> 6) << 6) + 64 + 0.0001;
		lmx->ry = (lmx->rx - lmx->px) * ratan + lmx->py;
		lmx->xo = 64;
		lmx->yo = lmx->xo * ratan;
	}
	ray_y2(lmx);
}

static void	draw_ray(t_win*lmx, float ra, int c)
{
	float	wall_x;
	int		side;

	if (lmx->d_v >= 1000000 && lmx->d_h >= 1000000)
		return ;
	if (lmx->d_v < lmx->d_h)
	{
		lmx->d_t = dist(lmx->px, lmx->py, lmx->vx, lmx->vy) * cos(ra - lmx->pa);
		if (ra > PI / 2 && ra < 3 * PI / 2)
			side = 2;
		else
			side = 3;
		wall_x = fmod(lmx->vy, 64) / 64.0f;
	}
	else
	{
		lmx->d_t = dist(lmx->px, lmx->py, lmx->hx, lmx->hy) * cos(ra - lmx->pa);
		if (ra > PI)
			side = 0;
		else
			side = 1;
		wall_x = fmod(lmx->hx, 64) / 64.0f;
	}
	draw_line(lmx, c, (int)(wall_x * lmx->tex[side].width), &lmx->tex[side]);
}

void	rays(t_win*lmx, int r, float ra, float ratan)
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
		ray_y(lmx, &ra, ratan);
		draw_ray(lmx, ra, c);
		ra += (60 * DR) / 1920;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}
