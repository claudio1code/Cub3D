/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:55:44 by cacesar-          #+#    #+#             */
/*   Updated: 2026/03/23 18:03:11 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//119 = w
//97 = a
//115 = s
//100 = d

#include <stdio.h>

static void	limits(t_win*lmx, int ix, int iy, int k_code)
{
	if (k_code == 119 || k_code == 97)
	{
		if (lmx->matrix[iy][(lmx->px - 2) / 64] == 1
			&& lmx->py / 64 == iy && k_code == 97)
				lmx->px = (((lmx->px + 63) / 64) * 64) + 2;
		if (lmx->matrix[(lmx->py - 2) / 64][ix] == 1
			&& lmx->px / 64 == ix && k_code == 119)
				lmx->py = (((lmx->py + 63) / 64) * 64) + 2;
	}
	else if (k_code == 115 || k_code == 100)
	{
		if (lmx->matrix[iy][(lmx->px + 2) / 64] == 1
			&& lmx->py / 64 == iy && k_code == 100)
				lmx->px = (lmx->px - (lmx->px + 2) % 64) - 2;
		if (lmx->matrix[(lmx->py + 2) / 64][ix] == 1
			&& lmx->px / 64 == ix && k_code == 115)
			lmx->py = (lmx->py - (lmx->py + 2) % 64) - 2;
	}
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
				&& x <= 64 *(ix + 1) - 2 && y <= 64 *(iy + 1) - 2)
				*(unsigned *)i = 0xFF0000;
			if (x >= lmx->px - 2 && x <= lmx->px + 2
				&& y >= lmx->py - 2 && y <= lmx->py + 2
				&& lmx->matrix[lmx->py / 64][ix] != 1
				&& lmx->matrix[iy][lmx->px / 64] != 1)
				*(unsigned *)i = 0x008000;
		}
	}
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
}

static void	m_paint(t_win*lmx, int k_code)
{
	int			ix;
	int			iy;

	mlx_destroy_image(lmx->lmx, lmx->img);
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1920);
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	ix = -1;
	while (++ix <= 4)
	{
		iy = -1;
		while (++iy <= 4)
		{
			limits(lmx, ix, iy, k_code);
			paint_m(lmx, iy, ix);
		}
	}
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
}

static int	key_hooked(int k_code, t_win*lmx)
{
	if (k_code == 65307)
		close_window(lmx);
	else if (k_code == 119 || k_code == 97)
	{
		if (k_code == 119)
			lmx->py -= 5;
		else
			lmx->px -= 5;
		m_paint(lmx, k_code);
	}
	else if (k_code == 115 || k_code == 100)
	{
		if (k_code == 115)
			lmx->py += 5;
		else
			lmx->px += 5;
		m_paint(lmx, k_code);
	}
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
	mlx_key_hook(lmx->win, key_hooked, lmx);
	mlx_hook(lmx->win, 17, 0, close_window, lmx);
	//mlx_loop_hook();
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
