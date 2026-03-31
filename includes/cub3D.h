/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:17:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/31 11:50:09 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.1415926535
# define DR 0.0174533

# include "libft.h"
# include "stdio.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/X.h>
# include <math.h>

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

typedef struct s_libx
{
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			oldpy;
	float			oldpx;
	float			pa;
	float			d_h;
	float			hx;
	float			hy;
	float			d_v;
	float			vx;
	float			vy;
	float			d_t;
	float			l_h;
	float			atan;
	int				ll;
	int				bpp;
	int				endian;
	int				matrix_s;
	int				w;
	int				a;
	int				s;
	int				d;
	char			*addr;
	void			*lmx;
	void			*win;
	void			*img;
	float			**matrix;
}	t_win;

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
int		validate_wall(t_infoMaps *data);


#endif