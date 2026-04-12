/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:55:44 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 11:52:24 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_win *lmx)
{
	if (!lmx)
		exit(1);
	free_info_maps(lmx->map_data);
	ft_lstclear(&lmx->file_lst, free, 0);
	get_next_line(-1);
	free_win(lmx);
	exit(0);
	return (0);
}

void	game(t_win *lmx)
{
	mlx_put_image_to_window(lmx->lmx, lmx->win, lmx->img, 0, 0);
	mlx_hook(lmx->win, 6, 1L << 6, mouse_move, lmx);
	mlx_mouse_hide(lmx->lmx, lmx->win);
	mlx_hook(lmx->win, 17, 0, (void *)close_window, lmx);
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

static void	init_game_error(t_win *lmx, t_infoMaps *data, t_list *file)
{
	free_info_maps(data);
	ft_lstclear(&file, free, 0);
	get_next_line(-1);
	free_win(lmx);
}

void	init_game(t_infoMaps *data, t_list *file)
{
	t_win	*lmx;

	lmx = ft_calloc(1, sizeof(t_win));
	if (!lmx)
		return ;
	lmx->map_data = data;
	lmx->file_lst = file;
	lmx->matrix_s = data->height;
	if (!alloc_matrix(lmx, data))
		return (init_game_error(lmx, data, file));
	lmx->lmx = mlx_init();
	if (!lmx->lmx)
		return (init_game_error(lmx, data, file));
	if (!init_textures(lmx))
		return (init_game_error(lmx, data, file));
	lmx->win = mlx_new_window(lmx->lmx, 1920, 1024, "cub3D");
	if (!lmx->win)
		return (init_game_error(lmx, data, file));
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1024);
	if (!lmx->img)
		return (init_game_error(lmx, data, file));
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	set_player_info(lmx, data);
	game(lmx);
}
