/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:38:46 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 09:44:29 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	ray_x2(t_win*lmx)
{
	while (1)
	{
		if ((int)lmx->ry >> 6 >= lmx->matrix_s
			|| (int)lmx->rx >> 6 >= lmx->matrix_s
			|| (int)lmx->rx >> 6 < 0 || (int)lmx->ry >> 6 < 0)
			break ;
		if (lmx->matrix[(int)lmx->ry >> 6][(int)lmx->rx >> 6] == 1)
		{	
			lmx->d_h = dist(lmx->px, lmx->py, lmx->rx, lmx->ry);
			lmx->hx = lmx->rx;
			lmx->hy = lmx->ry;
			break ;
		}
		else
		{
			lmx->rx += lmx->xo;
			lmx->ry += lmx->yo;
		}
	}
}

void	ray_y2(t_win*lmx)
{
	while (1)
	{
		if ((int)lmx->ry >> 6 >= lmx->matrix_s
			|| (int)lmx->rx >> 6 >= lmx->matrix_s
			|| (int)lmx->rx >> 6 < 0 || (int)lmx->ry >> 6 < 0)
			break ;
		if (lmx->matrix[(int)lmx->ry >> 6][(int)lmx->rx >> 6] == 1)
		{
			lmx->d_v = dist(lmx->px, lmx->py, lmx->rx, lmx->ry);
			lmx->vx = lmx->rx;
			lmx->vy = lmx->ry;
			break ;
		}
		else
		{
			lmx->rx += lmx->xo;
			lmx->ry += lmx->yo;
		}
	}
}

void	movement_2(t_win*lmx)
{
	if (lmx->l)
	{
		lmx->pa -= 0.05f;
		if (lmx->pa < 0)
			lmx->pa += 2 * PI;
		lmx->pdx = cos(lmx->pa) * 2;
		lmx->pdy = sin(lmx->pa) * 2;
	}
	if (lmx->r)
	{
		lmx->pa += 0.05f;
		if (lmx->pa >= 2 * PI)
			lmx->pa -= 2 * PI;
		lmx->pdx = cos(lmx->pa) * 2;
		lmx->pdy = sin(lmx->pa) * 2;
	}
}

void	blackout(t_win*lmx, int x, int y)
{
	char	*i;

	while (++x <= 320)
	{
		y = -1;
		while (++y <= 320)
		{
			i = lmx->addr + (y * lmx->ll + x * (lmx->bpp / 8));
			*(unsigned *)i = 0x000000;
		}
	}
}
