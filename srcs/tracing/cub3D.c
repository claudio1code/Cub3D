/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:55:44 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/08 20:19:45 by cacesar-         ###   ########.fr       */
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
static void	ray_x(t_win*lmx, float*ra, float ratan);
static void	ray_x2(t_win*lmx);
static void	ray_y(t_win*lmx, float*ra, float ratan);
static void	ray_y2(t_win*lmx);

static int	mouse_move(int x, int y, t_win *lmx)
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

static float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
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

static void	ray_x2(t_win*lmx)
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

static void	ray_y2(t_win*lmx)
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

static void	rays(t_win*lmx, int r, float ra, float ratan)
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

static float	hot_fix(t_win*lmx, float dx, float dy, int flag)
{
	if (flag)
		return ((dx * cos(-lmx->pa - S) - dy * sin(-lmx->pa - S)) + 160);
	else
		return ((dx * sin(-lmx->pa - S) + dy * cos(-lmx->pa - S)) + 160);
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

void	game(t_win*lmx)
{
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	mlx_hook(lmx->win, 6, 1L << 6, mouse_move, lmx);
	mlx_mouse_hide(lmx->lmx, lmx->win);
	mlx_hook(lmx->win, 17, 0, close_window, lmx);
	mlx_hook(lmx->win, 2, 1L << 0, key_press, lmx);
	mlx_hook(lmx->win, 3, 1L << 1, key_release, lmx);
	mlx_loop_hook(lmx->lmx, paint, lmx);
	mlx_loop(lmx->lmx);
}

void	init_init(t_win*lmx)
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
}

void	init(t_win*lmx, float ix, float iy)
{
	init_init(lmx);
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
