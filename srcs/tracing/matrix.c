/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:42:00 by claudio          #+#    #+#             */
/*   Updated: 2026/04/11 21:42:00 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	alloc_matrix(t_win *lmx, t_infoMaps *data)
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
