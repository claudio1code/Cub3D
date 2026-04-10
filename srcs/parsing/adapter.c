/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 23:59:00 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/09 23:59:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_player_dir(t_win *lmx, t_infoMaps *data)
{
	if (data->p_dir == 'N')
		lmx->pa = N;
	else if (data->p_dir == 'S')
		lmx->pa = S;
	else if (data->p_dir == 'E')
		lmx->pa = E;
	else if (data->p_dir == 'W')
		lmx->pa = W;
}

static void	fill_matrix(t_win *lmx, t_infoMaps *data, int iy, int ix)
{
	if (data->width > data->height)
		lmx->matrix_s = data->width;
	else
		lmx->matrix_s = data->height;
	lmx->matrix = ft_calloc(lmx->matrix_s, sizeof(float *));
	iy = -1;
	while (++iy < lmx->matrix_s)
	{
		lmx->matrix[iy] = ft_calloc(lmx->matrix_s, sizeof(float));
		ix = -1;
		while (++ix < lmx->matrix_s)
		{
			if (iy < data->height && ix < data->width)
			{
				if (data->grid[iy][ix] == '1' || data->grid[iy][ix] == ' '
					|| data->grid[iy][ix] == '\0')
					lmx->matrix[iy][ix] = 1.0f;
				else if (data->grid[iy][ix] == '0')
					lmx->matrix[iy][ix] = 0.0f;
				else
					lmx->matrix[iy][ix] = 2.0f;
			}
			else
				lmx->matrix[iy][ix] = 1.0f;
		}
	}
}

static int	load_textures(t_win *lmx, t_infoMaps *data)
{
	lmx->tex[0].img = mlx_xpm_file_to_image(lmx->lmx, data->no_texture,
			&lmx->tex[0].width, &lmx->tex[0].height);
	if (!lmx->tex[0].img) return (ft_putstr_fd("Error\nNO tex\n", 2), 0);
	lmx->tex[0].addr = mlx_get_data_addr(lmx->tex[0].img, &lmx->tex[0].bpp, &lmx->tex[0].ll, &lmx->tex[0].endian);

	lmx->tex[1].img = mlx_xpm_file_to_image(lmx->lmx, data->so_texture,
			&lmx->tex[1].width, &lmx->tex[1].height);
	if (!lmx->tex[1].img) return (ft_putstr_fd("Error\nSO tex\n", 2), 0);
	lmx->tex[1].addr = mlx_get_data_addr(lmx->tex[1].img, &lmx->tex[1].bpp, &lmx->tex[1].ll, &lmx->tex[1].endian);

	lmx->tex[2].img = mlx_xpm_file_to_image(lmx->lmx, data->we_texture,
			&lmx->tex[2].width, &lmx->tex[2].height);
	if (!lmx->tex[2].img) return (ft_putstr_fd("Error\nWE tex\n", 2), 0);
	lmx->tex[2].addr = mlx_get_data_addr(lmx->tex[2].img, &lmx->tex[2].bpp, &lmx->tex[2].ll, &lmx->tex[2].endian);

	lmx->tex[3].img = mlx_xpm_file_to_image(lmx->lmx, data->ea_texture,
			&lmx->tex[3].width, &lmx->tex[3].height);
	if (!lmx->tex[3].img) return (ft_putstr_fd("Error\nEA tex\n", 2), 0);
	lmx->tex[3].addr = mlx_get_data_addr(lmx->tex[3].img, &lmx->tex[3].bpp, &lmx->tex[3].ll, &lmx->tex[3].endian);

	return (1);
}

void	start_engine(t_infoMaps *data)
{
	t_win	*lmx;

	lmx = malloc(sizeof(t_win));
	ft_bzero(lmx, sizeof(t_win));
	lmx->ceil_c = data->ceiling_color;
	lmx->floor_c = data->floor_color;
	lmx->lmx = mlx_init();
	lmx->win = mlx_new_window(lmx->lmx, 1920, 1024, "cub3D");
	lmx->img = mlx_new_image(lmx->lmx, 1920, 1024);
	lmx->addr = mlx_get_data_addr(lmx->img, &lmx->bpp, &lmx->ll, &lmx->endian);
	set_player_dir(lmx, data);
	lmx->pdx = cos(lmx->pa) * 2;
	lmx->pdy = sin(lmx->pa) * 2;
	lmx->px = (data->p_x * 64.0f) + 32.0f;
	lmx->py = (data->p_y * 64.0f) + 32.0f;
	fill_matrix(lmx, data, 0, 0);
	load_textures(lmx, data);
	game(lmx);
}
