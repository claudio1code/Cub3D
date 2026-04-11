/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:05:00 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/11 12:05:00 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_background(t_win *lmx)
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
				*dst = lmx->map_data->ceiling_color;
			else
				*dst = lmx->map_data->floor_color;
		}
	}
}

void	draw_line(t_win *lmx, int x, int tex_x, t_tex *tex)
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

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	paint(void *lm)
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
