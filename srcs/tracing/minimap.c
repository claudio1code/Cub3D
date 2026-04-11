/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:15:00 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/11 12:15:00 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	blackout(t_win *lmx, int x, int y)
{
	char	*i;

	while (++x <= 320)
	{
		y = -1;
		while (++y <= 320)
		{
			i = lmx->addr + (y * lmx->ll + x * (lmx->bpp / 8));
			*(unsigned int *)i = 0x000000;
		}
	}
}

static float	hot_fix(t_win *lmx, float dx, float dy, int flag)
{
	if (flag)
		return ((dx * cos(-lmx->pa - S) - dy * sin(-lmx->pa - S)) + 160);
	else
		return ((dx * sin(-lmx->pa - S) + dy * cos(-lmx->pa - S)) + 160);
}

static void	paint_m(t_win *lmx, float iy, float ix, char *i)
{
	float		x;
	float		y;
	float		x_m;
	float		y_m;

	x = 64 * ix - 1;
	while (++x < 64 * (ix + 1))
	{
		y = 64 * iy - 1;
		while (++y < 64 * (iy + 1))
		{
			x_m = hot_fix(lmx, x - lmx->px, y - lmx->py, 1);
			y_m = hot_fix(lmx, x - lmx->px, y - lmx->py, 0);
			if (x_m < 0 || x_m > 320 || y_m < 0 || y_m > 320)
				continue ;
			i = lmx->addr + ((int)y_m * lmx->ll + (int)x_m * (lmx->bpp / 8));
			if (lmx->matrix[(int)iy][(int)ix] == 1)
				*(unsigned int *)i = 0xFF0000;
			else if (lmx->matrix[(int)iy][(int)ix] == 0
				|| lmx->matrix[(int)iy][(int)ix] == 2)
				*(unsigned int *)i = 0x333333;
			if (x_m >= 158 && x_m <= 162 && y_m >= 158 && y_m <= 162)
				*(unsigned int *)i = 0x00FF00;
		}
	}
}

void	m_paint(t_win *lmx)
{
	int			ix;
	int			iy;

	ix = -1;
	blackout(lmx, -1, -1);
	while (++ix < lmx->map_data->width)
	{
		iy = -1;
		while (++iy < lmx->map_data->height)
			paint_m(lmx, iy, ix, 0);
	}
}
