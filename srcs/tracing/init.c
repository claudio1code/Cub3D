/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:04:31 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 09:48:34 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static float	hot_fix(t_win*lmx, float dx, float dy, int flag)
{
	if (flag)
		return ((dx * cos(-lmx->pa - S) - dy * sin(-lmx->pa - S)) + 160);
	else
		return ((dx * sin(-lmx->pa - S) + dy * cos(-lmx->pa - S)) + 160);
}

static void	init_init(t_win*lmx)
{
	lmx->lmx = mlx_init();
	lmx->win = mlx_new_window(lmx->lmx, 1920, 1024, "teste");
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1024);
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	lmx->pa = (3 * PI) / 2;
	lmx->pdx = cos(lmx->pa) * 2;
	lmx->pdy = sin(lmx->pa) * 2;
	lmx->tex[0].img = mlx_xpm_file_to_image(lmx->lmx, "textures/B01.xpm",
			&lmx->tex[0].width, &lmx->tex[0].height);
	lmx->tex[0].addr = mlx_get_data_addr(lmx->tex[0].img,
			&lmx->tex[0].bpp, &lmx->tex[0].ll, &lmx->tex[0].endian);
	lmx->tex[1].img = mlx_xpm_file_to_image(lmx->lmx, "textures/B02.xpm",
			&lmx->tex[1].width, &lmx->tex[1].height);
	lmx->tex[1].addr = mlx_get_data_addr(lmx->tex[1].img,
			&lmx->tex[1].bpp, &lmx->tex[1].ll, &lmx->tex[1].endian);
	lmx->tex[2].img = mlx_xpm_file_to_image(lmx->lmx, "textures/B03.xpm",
			&lmx->tex[2].width, &lmx->tex[2].height);
	lmx->tex[2].addr = mlx_get_data_addr(lmx->tex[2].img,
			&lmx->tex[2].bpp, &lmx->tex[2].ll, &lmx->tex[2].endian);
	lmx->tex[3].img = mlx_xpm_file_to_image(lmx->lmx, "textures/B04.xpm",
			&lmx->tex[3].width, &lmx->tex[3].height);
	lmx->tex[3].addr = mlx_get_data_addr(lmx->tex[3].img,
			&lmx->tex[3].bpp, &lmx->tex[3].ll, &lmx->tex[3].endian);
	lmx->w = 0;
	lmx->a = 0;
}

void	init(t_win*lmx, float ix, float iy)
{
	init_init(lmx);
	lmx->s = 0;
	lmx->d = 0;
	lmx->r = 0;
	lmx->l = 0;
	while (++ix <= 4)
	{
		iy = -1;
		while (++iy <= 4)
		{
			if (lmx->matrix[(int)iy][(int)ix] == 2)
				lmx->px = (64 * (ix + 1)) - 32;
			if (lmx->matrix[(int)iy][(int)ix] == 2)
				lmx->py = (64 * (iy + 1)) - 32;
		}
	}
	ix = -1;
	while (++ix <= 4)
	{
		iy = -1;
		while (++iy <= 4)
			paint_m(lmx, ix, iy, 0);
	}
	game(lmx);
}

void	paint_m(t_win*lmx, float iy, float ix, char*i)
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
				*(unsigned *)i = 0xFF0000;
			else if (lmx->matrix[(int)iy][(int)ix] == 0
				|| lmx->matrix[(int)iy][(int)ix] == 2)
				*(unsigned *)i = 0x333333;
			if (x_m >= 158 && x_m <= 162 && y_m >= 158 && y_m <= 162)
				*(unsigned *)i = 0x00FF00;
		}
	}
}
