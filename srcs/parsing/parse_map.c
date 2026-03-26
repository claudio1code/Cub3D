/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:43:07 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/26 17:10:57 by clados-s         ###   ########.fr       */
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
