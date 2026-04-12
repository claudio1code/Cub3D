/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:13:02 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 09:49:58 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	close_window(t_win*lmx)
{
	int	i;

	if (!lmx)
		exit(1);
	i = -1;
	while (++i < 4)
		if (lmx->tex[i].img)
			mlx_destroy_image(lmx->lmx, lmx->tex[i].img);
	if (lmx->img)
		mlx_destroy_image(lmx->lmx, lmx->img);
	if (lmx->win)
		mlx_destroy_window(lmx->lmx, lmx->win);
	if (lmx->lmx)
	{
		mlx_destroy_display(lmx->lmx);
		free(lmx->lmx);
	}
	if (lmx->matrix)
		ft_del_del_n((void **)lmx->matrix, lmx->matrix_s);
	free(lmx);
	exit (0);
}

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
	else if (k_code == 65361)
		lmx->l = 0;
	else if (k_code == 65363)
		lmx->r = 0;
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
	else if (k_code == 65361)
		lmx->l = 1;
	else if (k_code == 65363)
		lmx->r = 1;
	return (1);
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
