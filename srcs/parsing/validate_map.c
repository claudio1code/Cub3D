/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:14:59 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/10 12:00:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_enclosed(t_infoMaps *data, int y, int x)
{
	if (y == 0 || y == data->height - 1 || x == 0 || x == data->width - 1)
		return (0);
	if (data->grid[y - 1][x] == ' ' || data->grid[y + 1][x] == ' ' || \
		data->grid[y][x - 1] == ' ' || data->grid[y][x + 1] == ' ')
		return (0);
	if (data->grid[y - 1][x - 1] == ' ' || data->grid[y - 1][x + 1] == ' ' || \
		data->grid[y + 1][x - 1] == ' ' || data->grid[y + 1][x + 1] == ' ')
		return (0);
	return (1);
}

int	validate_wall(t_infoMaps *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->grid[y][x] == '0' || data->grid[y][x] == 'N' || \
				data->grid[y][x] == 'S' || data->grid[y][x] == 'E' || \
				data->grid[y][x] == 'W')
			{
				if (!is_enclosed(data, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
