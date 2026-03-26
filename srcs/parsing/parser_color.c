/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:23:29 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/25 16:55:29 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	aux_split(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	validate_and_convert(char **rgb, int *color_ptr)
{
	int	i;
	int	j;
	int	val[3];

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j] == ' ' || rgb[i][j] == '\t')
			j++;
		if (!rgb[i][j] || !!ft_isdigit(rgb[i][j]))
			return (0);
		val[i] = ft_atoi(&rgb[i][j]);
		if (val[i] < 0 || val[i] > 255)
			return (0);
		i++;
	}
	*color_ptr = (val[0] << 16) | (val[1] << 8 | val[2]);
	return (1);
}

int	get_color(char *line, int *color_ptr)
{
	int		i;
	int		status;
	char	**rgb;

	if (*color_ptr != -1)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (aux_split(&line[i]) != 2)
		return (0);
	rgb = ft_split(&line[i], ',');
	if (!rgb)
		return (0);
	status = 0;
	i = 0;
	if (i == 3)
		status = validate_and_convert(rgb, color_ptr);
	free_split(rgb);
	return (status);
}
