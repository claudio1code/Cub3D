/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:05:36 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 14:59:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_player(t_infoMaps *data, int y, int x, int *players)
{
	char	c;

	c = data->grid[y][x];
	if (!is_valid_char(c))
		return (0);
	if (is_player(c))
	{
		(*players)++;
		data->p_y = y;
		data->p_x = x;
		data->p_dir = c;
		data->grid[y][x] = '0';
	}
	return (1);
}

int	validate_map_char(t_infoMaps *data)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data-> width)
		{
			if (!check_player(data, y, x, &players))
				return (0);
			x++;
		}
		y++;
	}
	if (players != 1)
		return (0);
	return (1);
}
