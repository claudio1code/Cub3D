/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:55:44 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/11 12:20:00 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_win *lmx)
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
	exit(0);
}

void	game(t_win *lmx)
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

static void	set_player_info(t_win *lmx, t_infoMaps *data)
{
	lmx->px = (data->p_x * 64) + 32;
	lmx->py = (data->p_y * 64) + 32;
	if (data->p_dir == 'E')
		lmx->pa = 0.0;
	else if (data->p_dir == 'S')
		lmx->pa = PI / 2.0;
	else if (data->p_dir == 'W')
		lmx->pa = PI;
	else if (data->p_dir == 'N')
		lmx->pa = (3.0 * PI) / 2.0;
	lmx->pdx = cos(lmx->pa) * 2;
	lmx->pdy = sin(lmx->pa) * 2;
}

static int	alloc_matrix(t_win *lmx, t_infoMaps *data)
{
	int	ix;
	int	iy;

	lmx->matrix = ft_calloc(data->height, sizeof(float *));
	if (!lmx->matrix)
		return (0);
	iy = -1;
	while (++iy < data->height)
	{
		lmx->matrix[iy] = ft_calloc(data->width, sizeof(float));
		if (!lmx->matrix[iy])
			return (0);
		ix = -1;
		while (++ix < data->width)
		{
			if (data->grid[iy][ix] == '1')
				lmx->matrix[iy][ix] = 1;
			else if (data->grid[iy][ix] == ' ' || data->grid[iy][ix] == '0'
				|| data->grid[iy][ix] == 'N' || data->grid[iy][ix] == 'S'
				|| data->grid[iy][ix] == 'E' || data->grid[iy][ix] == 'W')
				lmx->matrix[iy][ix] = (data->grid[iy][ix] != ' '
						&& data->grid[iy][ix] != '0') * 2;
		}
	}
	return (1);
}

void	init_game(t_infoMaps *data)
{
	t_win	*lmx;

	lmx = ft_calloc(1, sizeof(t_win));
	if (!lmx)
		return ;
	lmx->map_data = data;
	lmx->matrix_s = data->height;
	if (!alloc_matrix(lmx, data))
		return (free_win(lmx));
	lmx->lmx = mlx_init();
	if (!lmx->lmx)
		return (free_win(lmx));
	if (!init_textures(lmx))
		return (free_win(lmx));
	lmx->win = mlx_new_window(lmx->lmx, 1920, 1024, "cub3D");
	if (!lmx->win)
		return (free_win(lmx));
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1024);
	if (!lmx->img)
		return (free_win(lmx));
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	set_player_info(lmx, data);
	game(lmx);
}
