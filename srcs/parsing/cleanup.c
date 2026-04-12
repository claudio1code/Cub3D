/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:30:00 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/11 21:21:43 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_info_maps(t_infoMaps *data)
{
	int	i;

	if (!data)
		return ;
	if (data->no_texture)
		free(data->no_texture);
	if (data->so_texture)
		free(data->so_texture);
	if (data->we_texture)
		free(data->we_texture);
	if (data->ea_texture)
		free(data->ea_texture);
	if (data->grid)
	{
		i = -1;
		while (data->grid[++i])
			free(data->grid[i]);
		free(data->grid);
	}
}

static void	free_textures(t_win *lmx)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (lmx->tex[i].img)
			mlx_destroy_image(lmx->lmx, lmx->tex[i].img);
	}
}

void	free_win(t_win *lmx)
{
	int	i;

	if (!lmx)
		return ;
	if (lmx->matrix)
	{
		i = -1;
		while (++i < lmx->matrix_s)
			free(lmx->matrix[i]);
		free(lmx->matrix);
	}
	if (lmx->img)
		mlx_destroy_image(lmx->lmx, lmx->img);
	free_textures(lmx);
	if (lmx->win)
		mlx_destroy_window(lmx->lmx, lmx->win);
	if (lmx->lmx)
	{
		mlx_destroy_display(lmx->lmx);
		free(lmx->lmx);
	}
	free(lmx);
}
