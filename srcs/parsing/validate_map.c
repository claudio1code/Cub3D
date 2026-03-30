/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:14:59 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 17:00:01 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**map_copy(t_infoMaps *data)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (data->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		copy[i] = ft_strdup(data->grid[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	flood_fill(char **map, int x, int y, t_infoMaps *data)
{
	if (x < 0 || y < 0 || y >= data->height || x >= data->width)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, x + 1, y, data) || \
		!flood_fill(map, x - 1, y, data) || \
		!flood_fill(map, x, y + 1, data) || \
		!flood_fill(map, x, y - 1, data))
		return (0);
	return (1);
}

int	validate_wall(t_infoMaps *data)
{
	char	**copy;
	int		is_valid;

	copy = map_copy(data);
	if (!copy)
		return (0);
	is_valid = flood_fill(copy, data->p_x, data->p_y, data);
	free_split(copy);
	return (is_valid);
}
