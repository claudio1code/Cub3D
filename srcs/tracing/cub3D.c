/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:55:44 by cacesar-          #+#    #+#             */
/*   Updated: 2026/03/30 18:12:01 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//119 = w
//97 = a
//115 = s
//100 = d

#include <stdio.h>

static void	paint_m(t_win*lmx, float iy, float ix, char*i);
static void	m_paint(t_win*lmx);

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

static void	draw_line(t_win *lmx, int x, int line_h, int vert)
{
	int		y;
	int		start;
	char	*dst;

	start = (1024 / 2) - (line_h / 2);
	if (start < 0)
		start = 0;
	y = -1;
	while (++y < line_h && (y + start) < 1024)
	{
		dst = lmx->addr + ((y + start) * lmx->ll + x * (lmx->bpp / 8));
		if (vert)
			*(unsigned *)dst = 0x880000;
		else
			*(unsigned *)dst = 0xFF0000;
	}
}

static float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

static void	rays(t_win*lmx, int r, float ra, float ratan)
{
	int		c;
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	c = -1;
	while (++c < r)
	{
		ratan = -1 / tan(ra);
		lmx->atan = ratan;
		if (lmx->atan > 100)
			lmx->atan = 100;
		if (lmx->atan < -100)
			lmx->atan = -100;
		lmx->d_h = 1000000;
		lmx->hx = lmx->px;
		lmx->hy = lmx->py;
		if (ra > PI)
		{
			ry = (((int)lmx->py >> 6) << 6) - 0.0001;
			rx = (lmx->py - ry) * ratan + lmx->px;
			yo = -64;
			xo = -yo * ratan;
		}
		if (ra < PI)
		{
			ry = (((int)lmx->py >> 6) << 6) + 64 + 0.0001;
			rx = (lmx->py - ry) * ratan + lmx->px;
			yo = 64;
			xo = -yo * ratan;
		}
		if (ra < 0.001 || fabs(ra - PI) < 0.001)
		{
			rx = lmx->px;
			ry = lmx->py;
		}
		while (1)
		{
			if ((int)ry >> 6 >= lmx->matrix_s || (int)rx >> 6 >= lmx->matrix_s
				|| (int)rx >> 6 < 0 || (int)ry >> 6 < 0)
				break ;
			if (lmx->matrix[(int)ry >> 6][(int)rx >> 6] == 1)
			{	
				lmx->d_h = dist(lmx->px, lmx->py, rx, ry);
				lmx->hx = rx;
				lmx->hy = ry;
				break ;
			}
			else
			{
				rx += xo;
				ry += yo;
			}
		}
		ratan = tan(ra);
		lmx->atan = ratan;
		if (lmx->atan > 100)
			lmx->atan = 100;
		if (lmx->atan < -100)
			lmx->atan = -100;
		lmx->d_v = 1000000;
		lmx->vx = lmx->px;
		lmx->vy = lmx->py;
		if (ra > PI / 2 && ra < 3 * PI / 2)
		{
			rx = (((int)lmx->px >> 6) << 6) - 0.0001;
			ry = (rx - lmx->px) * ratan + lmx->py;
			xo = -64;
			yo = xo * ratan;
		}
		if (ra < PI / 2 || ra > 3 * PI / 2)
		{
			rx = (((int)lmx->px >> 6) << 6) + 64 + 0.0001;
			ry = (rx - lmx->px) * ratan + lmx->py;
			xo = 64;
			yo = xo * ratan;
		}
		if (ra < 0.001 || fabs(ra - PI) < 0.001)
		{
			rx = lmx->px;
			ry = lmx->py;
		}
		while (1)
		{
			if ((int)ry >> 6 >= lmx->matrix_s || (int)rx >> 6 >= lmx->matrix_s
				|| (int)rx >> 6 < 0 || (int)ry >> 6 < 0)
				break ;
			if (lmx->matrix[(int)ry >> 6][(int)rx >> 6] == 1)
			{
				lmx->d_v = dist(lmx->px, lmx->py, rx, ry);
				lmx->vx = rx;
				lmx->vy = ry;
				break ;
			}
			else
			{
				rx += xo;
				ry += yo;
			}
		}
		if (lmx->d_v < lmx->d_h)
		{
			lmx->d_t = dist(lmx->px, lmx->py, lmx->vx, lmx->vy) * cos(ra - lmx->pa);
			if (lmx->d_t < 0.1)
				lmx->d_t = 0.1;
			lmx->l_h = (64 * 1024) / lmx->d_t;
			if (lmx->l_h > 1024)
				lmx->l_h = 1024;
			draw_line(lmx, c, lmx->l_h, 1);
		}
		else
		{
			lmx->d_t = dist(lmx->px, lmx->py, lmx->hx, lmx->hy) * cos(ra - lmx->pa);
			if (lmx->d_t < 0.1)
				lmx->d_t = 0.1;
			lmx->l_h = (64 * 1024) / lmx->d_t;
			if (lmx->l_h > 1024)
				lmx->l_h = 1024;
			draw_line(lmx, c, lmx->l_h, 0);
		}
		ra += (60 * DR) / 1920;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

static void	movement(t_win*lmx)
{
	if (lmx->a)
		lmx->pa -= 0.1;
	if (lmx->d)
		lmx->pa += 0.1;
	if (lmx->pa < 0)
		lmx->pa += (2 * PI);
	if (lmx->pa >= (2 * PI))
		lmx->pa -= (2 * PI);
	if (lmx->a || lmx->d)
		lmx->pdx = cos(lmx->pa) * 5;
	if (lmx->a || lmx->d)
		lmx->pdy = sin(lmx->pa) * 5;
	if (lmx->w)
		lmx->px += lmx->pdx;
	if (lmx->w)
		lmx->py += lmx->pdy;
	if (lmx->s)
		lmx->px -= lmx->pdx;
	if (lmx->s)
		lmx->py -= lmx->pdy;
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

static void	blackout(t_win*lmx, int x, int y)
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

static int	paint(void*lm)
{
	t_win		*lmx;
	int			c;

	lmx = (t_win *)lm;
	c = 0;
	lmx->oldpx = lmx->px;
	lmx->oldpy = lmx->py;
	movement(lmx);
	limits(lmx);
	draw_background(lmx);
	rays(lmx, 1920, lmx->pa - (30.0 * DR), 0);
	m_paint(lmx);
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	while (c < 20005000)
		c++;
	return (1);
}

static void	m_paint(t_win*lmx)
{
	int			ix;
	int			iy;

	if (!lmx->w && !lmx->a && !lmx->s && !lmx->d)
		return ;
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

static int	key_release(int k_code, t_win*lmx)
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

static int	key_press(int k_code, t_win*lmx)
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

static void	paint_m(t_win*lmx, float iy, float ix, char*i)
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
			x_m = ((x - lmx->px) + 160);
			y_m = ((y - lmx->py) + 160);
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

void	game(t_win*lmx)
{
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	mlx_hook(lmx->win, 17, 0, close_window, lmx);
	mlx_hook(lmx->win, 2, 1L << 0, key_press, lmx);
	mlx_hook(lmx->win, 3, 1L << 1, key_release, lmx);
	mlx_loop_hook(lmx->lmx, paint, lmx);
	mlx_loop(lmx->lmx);
}

void	init(t_win*lmx, float ix, float iy)
{
	lmx->lmx = mlx_init();
	lmx->win = mlx_new_window(lmx->lmx, 1920, 1024, "teste");
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1024);
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	lmx->pa = (3 * PI) / 2;
	lmx->pdx = cos(lmx->pa) * 5;
	lmx->pdy = sin(lmx->pa) * 5;
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

int	main(int argc, char**argv)
{
	t_win	*lmx;
	int		c;

	lmx = malloc(sizeof(t_win));
	lmx->matrix = ft_calloc(5, 8);
	argc = -1;
	lmx->matrix_s = 5;
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
	init(lmx, -1, -1);
	return (0);
}
