/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:10:00 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/11 12:10:00 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_win *lmx)
{
	int		center_x;
	float	delta;

	(void)y;
	center_x = 1920 / 2;
	delta = (x - center_x) * 0.002f;
	lmx->pa += delta;
	if (lmx->pa < 0)
		lmx->pa += 2 * PI;
	if (lmx->pa >= 2 * PI)
		lmx->pa -= 2 * PI;
	lmx->pdx = cos(lmx->pa) * 2;
	lmx->pdy = sin(lmx->pa) * 2;
	mlx_mouse_move(lmx->lmx, lmx->win, center_x, 512);
	return (1);
}

void	movement(t_win *lmx, float strafe_dx, float strafe_dy)
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
}

void	limits(t_win *lmx)
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

int	key_release(int k_code, t_win *lmx)
{
	if (k_code == 119)
		lmx->w = 0;
	else if (k_code == 97)
		lmx->a = 0;
	else if (k_code == 115)
		lmx->s = 0;
	else if (k_code == 100)
		lmx->d = 0;
	return (1);
}

int	key_press(int k_code, t_win *lmx)
{
	if (k_code == 65307)
		close_window(lmx);
	if (k_code == 119)
		lmx->w = 1;
	else if (k_code == 97)
		lmx->a = 1;
	else if (k_code == 115)
		lmx->s = 1;
	else if (k_code == 100)
		lmx->d = 1;
	return (1);
}
