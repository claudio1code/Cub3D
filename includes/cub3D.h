/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:17:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 12:46:15 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include "stdio.h"

typedef struct s_infoMaps
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	**grid;
	char	p_dir;
	float	p_y;
	float	p_x;
	int		floor_color;
	int		ceiling_color;
	int		height;
	int		width;
}	t_infoMaps;

t_list	*read_cub_file(char *filename);
t_list	*find_map_start(t_list *lst);
void	init_maps(t_infoMaps *data);
void	get_map_dimensions(t_list *map_start, t_infoMaps *data);
int		main(int argc, char **argv);
int		validate_args(int argc, char **argv);
int		parser_elements(char *line, t_infoMaps *data);
int		get_color(char *line, int *color_ptr);
int		validate_map_char(t_infoMaps *data);
int		extract_map(t_list *map_start, t_infoMaps *data);

#endif