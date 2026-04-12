/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:19:21 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 09:50:41 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	movement(t_win*lmx, float strafe_dx, float strafe_dy)
{
	lmx->pdx = cos(lmx->pa) * 2;
	lmx->pdy = sin(lmx->pa) * 2;
	strafe_dx = cos(lmx->pa + PI / 2) * 2;
	strafe_dy = sin(lmx->pa + PI / 2) * 2;
	if (lmx->w)
	{
		lmx->px += lmx->pdx;
		lmx->py += lmx->pdy;
	}
	if (lmx->s)
	{
		lmx->px -= lmx->pdx;
		lmx->py -= lmx->pdy;
	}
	if (lmx->a)
	{
		lmx->px -= strafe_dx;
		lmx->py -= strafe_dy;
	}
	if (lmx->d)
	{
		lmx->px += strafe_dx;
		lmx->py += strafe_dy;
	}
	movement_2(lmx);
}

static void	limits(t_win*lmx)
{
	if (lmx->matrix[(int)lmx->py / 64][(int)lmx->px / 64] == 1)
	{
		if (lmx->matrix[(int)lmx->oldpy / 64][(int)lmx->px / 64] != 1)
			lmx->py = lmx->oldpy;
		else if (lmx->matrix[(int)lmx->py / 64][(int)lmx->oldpx / 64] != 1)
			lmx->px = lmx->oldpx;
		else
		{
			lmx->px = lmx->oldpx;
			lmx->py = lmx->oldpy;
		}
	}
}

static void	draw_background(t_win *lmx)
{
	int				x;
	int				y;
	unsigned int	*dst;

	y = -1;
	while (++y < 1024)
	{
		x = -1;
		while (++x < 1920)
		{
			dst = (unsigned int *)(lmx->addr
					+ (y * lmx->ll + x * (lmx->bpp / 8)));
			if (y < 1024 / 2)
				*dst = 0x333333;
			else
				*dst = 0x777777;
		}
	}
}

static void	m_paint(t_win*lmx)
{
	int			ix;
	int			iy;

	ix = -1;
	blackout(lmx, -1, -1);
	while (++ix < lmx->matrix_s)
	{
		iy = -1;
		while (++iy < lmx->matrix_s)
			paint_m(lmx, iy, ix, 0);
	}
	ix = 0;
}

int	paint(void*lm)
{
	t_win		*lmx;
	int			c;

	lmx = (t_win *)lm;
	c = 0;
	lmx->oldpx = lmx->px;
	lmx->oldpy = lmx->py;
	movement(lmx, 0, 0);
	limits(lmx);
	draw_background(lmx);
	rays(lmx, 1920, lmx->pa - (30.0 * DR), 0);
	m_paint(lmx);
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	while (c < 20005000)
		c++;
	return (1);
}
