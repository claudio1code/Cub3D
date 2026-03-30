/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:43:07 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 14:58:02 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include "cub3D.h"

t_list	*find_map_start(t_list *lst)
{
	char	*line;
	int		i;

	while (lst)
	{
		line = (char *)lst->content;
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != '\n' && line[i] != '\0')
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	get_map_dimensions(t_list *map_start, t_infoMaps *data)
{
	char	*line;
	int		len;

	data->height = 0;
	data->width = 0;
	while (map_start)
	{
		line = (char *)map_start->content;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len > data->width)
			data->width = len;
		data->height++;
		map_start = map_start->next;
	}
}

static void	fill_row(char *grid_row, char *line, int width)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		grid_row[i] = line[i];
		i++;
	}
	while (i < width)
	{
		grid_row[i] = ' ';
		i++;
	}
	grid_row[width] = '\0';
}

int	extract_map(t_list *map_start, t_infoMaps *data)
{
	int	i;

	get_map_dimensions(map_start, data);
	if (data->width == 0 || data->height == 0)
		return (0);
	data->grid = malloc(sizeof(char *) * (data->height + 1));
	if (!data->grid)
		return (0);
	i = 0;
	while (map_start)
	{
		data->grid[i] = malloc(sizeof(char) * (data->width + 1));
		if (!data->grid[i])
			return (0);
		fill_row(data->grid[i], (char *)map_start->content, data->width);
		i++;
		map_start = map_start->next;
	}
	data->grid[i] = NULL;
	return (1);
}
