/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 10:33:55 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/10 10:10:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_single_texture(void *mlx_ptr, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->ll, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	init_textures(t_win *lmx)
{
	if (!load_single_texture(lmx->lmx, &lmx->tex[0],
			lmx->map_data->no_texture))
		return (ft_putstr_fd("Error\nFailed to load NO texture.\n", 2), 0);
	if (!load_single_texture(lmx->lmx, &lmx->tex[1],
			lmx->map_data->so_texture))
		return (ft_putstr_fd("Error\nFailed to load SO texture.\n", 2), 0);
	if (!load_single_texture(lmx->lmx, &lmx->tex[2],
			lmx->map_data->we_texture))
		return (ft_putstr_fd("Error\nFailed to load WE texture.\n", 2), 0);
	if (!load_single_texture(lmx->lmx, &lmx->tex[3],
			lmx->map_data->ea_texture))
		return (ft_putstr_fd("Error\nFailed to load EA texture.\n", 2), 0);
	return (1);
}
