/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:55:44 by cacesar-          #+#    #+#             */
/*   Updated: 2026/03/24 14:32:34 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//119 = w
//97 = a
//115 = s
//100 = d

#include <stdio.h>

static void	limits(t_win*lmx)
{
	if (lmx->w)
		lmx->py -= 2;
	if (lmx->a)
		lmx->px -= 2;
	if (lmx->s)
		lmx->py += 2;
	if (lmx->d)
		lmx->px += 2;
	if (lmx->matrix[lmx->py / 64][(lmx->px - 2) / 64] == 1 && lmx->a)
		lmx->px = (((lmx->px + 63) / 64) * 64) + 2;
	if (lmx->matrix[(lmx->py - 2) / 64][lmx->px / 64] == 1 && lmx->w)
		lmx->py = (((lmx->py + 63) / 64) * 64) + 2;
	if (lmx->matrix[lmx->py / 64][(lmx->px + 2) / 64] == 1 && lmx->d)
		lmx->px = (lmx->px - (lmx->px + 2) % 64) - 2;
	if (lmx->matrix[(lmx->py + 2) / 64][lmx->px / 64] == 1 && lmx->s)
		lmx->py = (lmx->py - (lmx->py + 2) % 64) - 2;
}

static int	close_window(t_win*lmx)
{
	if (!lmx)
		exit(1);
	if (lmx->img)
		mlx_destroy_image(lmx->lmx, lmx->img);
	if (lmx->win)
		mlx_destroy_window(lmx->lmx, lmx->win);
	if (lmx->lmx)
		mlx_destroy_display(lmx->lmx);
	if (lmx->lmx)
		free(lmx->lmx);
	free(lmx);
	exit (0);
}

static void	paint_m(t_win*lmx, int iy, int ix)
{
	int			x;
	int			y;
	char		*i;

	x = 64 * ix - 1;
	while (++x <= 64 * (ix + 1))
	{
		y = 64 * iy - 1;
		while (++y <= 64 * (iy + 1))
		{
			i = lmx->addr + (y * lmx->ll + x * (lmx->bpp / 8));
			if (lmx->matrix[iy][ix] == 1 && x >= 1 && y >= 1
				&& x <= 64 *(ix + 1) - 2 && y <= 64 *(iy + 1) - 2
				&& x <= lmx->px + 128 && x >= lmx->px - 128
				&& y <= lmx->py + 128 && y >= lmx->py - 128)
				*(unsigned *)i = 0xFF0000;
			else
				*(unsigned *)i = 0x000000;
			if (x >= lmx->px - 2 && x <= lmx->px + 2
				&& y >= lmx->py - 2 && y <= lmx->py + 2
				&& lmx->matrix[lmx->py / 64][ix] != 1
				&& lmx->matrix[iy][lmx->px / 64] != 1)
				*(unsigned *)i = 0x008000;
		}
	}
}

static int	m_paint(void*lm)
{
	int			ix;
	int			iy;
	t_win		*lmx;

	lmx = (t_win *)lm;
	if (!lmx->w && !lmx->a && !lmx->s && !lmx->d)
		return (0);
	ix = -1;
	limits(lmx);
	while (++ix <= 4)
	{
		iy = -1;
		while (++iy <= 4)
		{
			paint_m(lmx, iy, ix);
		}
	}
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	ix = 0;
	while (ix != 20050000)
		ix++;
	return (1);
}

static int	key_release(int k_code, t_win*lmx)
{
	if (k_code == 65307)
		close_window(lmx);
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

static int	key_press(int k_code, t_win*lmx)
{
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

static void	paint_i(t_win*lmx, int iy, int ix)
{
	int			x;
	int			y;
	char		*i;

	x = 64 * ix - 1;
	while (++x <= 64 * (ix + 1))
	{
		y = 64 * iy - 1;
		while (++y <= 64 * (iy + 1))
		{
			i = lmx->addr + (y * lmx->ll + x * (lmx->bpp / 8));
			if (lmx->matrix[iy][ix] == 2 && x >= lmx->px - 2
				&& x <= lmx->px + 2 && y >= lmx->py - 2 && y <= lmx->py + 2)
				*(unsigned *)i = 0x008000;
			if (lmx->matrix[iy][ix] == 1 && x >= 1 && y >= 1 &&
				x <= 64 *(ix + 1) - 2 && y <= 64 *(iy + 1) - 2)
				*(unsigned *)i = 0xFF0000;
		}
	}
}

void	game(t_win*lmx)
{
	mlx_hook(lmx->win, 17, 0, close_window, lmx);
	mlx_hook(lmx->win, 2, 1L << 0, key_press, lmx);
	mlx_hook(lmx->win, 3, 1L << 1, key_release, lmx);
	mlx_loop_hook(lmx->lmx, m_paint, lmx);
	mlx_loop(lmx->lmx);
}

void	init(t_win*lmx)
{
	int			ix;
	int			iy;

	lmx->lmx = mlx_init();
	lmx->px = 0;
	lmx->py = 0;
	lmx->win = mlx_new_window(lmx->lmx, 1920, 1920, "teste");
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1920);
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	ix = -1;
	while (++ix <= 4)
	{
		iy = -1;
		while (++iy <= 4)
		{
			if (lmx->matrix[iy][ix] == 2 && !lmx->px)
				lmx->px = (64 * (ix + 1)) - 32;
			if (lmx->matrix[iy][ix] == 2 && !lmx->py)
				lmx->py = (64 * (iy + 1)) - 32;
			paint_i(lmx, ix, iy);
		}
	}
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	game(lmx);
}

int	main(int argc, char**argv)
{
	t_win	*lmx;
	int		c;

	lmx = malloc(sizeof(t_win));
	lmx->matrix = ft_calloc(5, 8);
	argc = -1;
	while (++argc <= 4 && argv)
	{
		lmx->matrix[argc] = ft_calloc(5, sizeof(float));
		c = -1;
		while (++c <= 4)
		{
			if (!argc || argc == 4)
				lmx->matrix[argc][c] = 1;
			else if (!c || c == 4 || (argc == 2 && c == 2))
				lmx->matrix[argc][c] = 1;
			else if (c == 1 && argc == 3)
				lmx->matrix[argc][c] = 2;
			else
				lmx->matrix[argc][c] = 0;
		}
	}
	init(lmx);
	return (0);
}
