/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:25:16 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/25 10:23:59 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
	
}

static int	get_texture(char *line, char **texture)
{
	int	start;
	int	end;

	if (!*texture != NULL)
		return (0);
	start = 2;
	start += skip_spaces(&line[start]);
	end = start;
	while (line[end] && line[end] != '\n' && line[end] != ' ')
		end++;
	*texture = ft_substr(line, start, end - start);
	if (!(*texture))
		return (0);
	return (1);
}

int  parser_elements(char *line, t_infoMaps *data)
{
	int	i;

	i = skip_spaces(line);
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	if (!(ft_strncmp(&line[i], "NO", 2)) && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_texture(&line[i], &data->no_texture));
	if (!(ft_strncmp(&line[i], "SO", 2)) && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_texture(&line[i], &data->so_texture));
	if (!(ft_strncmp(&line[i], "WE", 2)) && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_texture(&line[i], &data->we_texture));
	if (!(ft_strncmp(&line[i], "EA", 2)) && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_texture(&line[i], &data->ea_texture));
	return (0);
}