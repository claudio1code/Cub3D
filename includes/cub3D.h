/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:17:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/10 13:00:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/X.h>
# include <math.h>
# include <stdio.h>

# define PI 3.1415926535
# define N 4.71238898025
# define E 6.283185307
# define S 1.57079632675
# define W 3.1415926535
# define DR 0.0174533

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_infoMaps
{
	t_tex		textures[4];
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		**grid;
	char		p_dir;
	float		p_y;
	float		p_x;
	int			floor_color;
	int			ceiling_color;
	int			height;
	int			width;
}	t_infoMaps;

typedef struct s_libx
{
	float			xo;
	float			yo;
	float			rx;
	float			ry;
	float			pa;
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			oldpy;
	float			oldpx;
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
	int				last_mx;
	char			*addr;
	void			*lmx;
	void			*win;
	void			*img;
	float			**matrix;
	t_tex			tex[4];
	t_infoMaps		*map_data;
}	t_win;

/* Parsing */
t_list	*read_cub_file(char *filename);
t_list	*find_map_start(t_list *lst);
void	get_map_dimensions(t_list *map_start, t_infoMaps *data);
void	init_maps(t_infoMaps *data);
int		extract_map(t_list *map_start, t_infoMaps *data);
int		parser_elements(char *line, t_infoMaps *data);
int		get_color(char *line, int *color_ptr);
int		validate_args(int argc, char **argv);
int		validate_map_char(t_infoMaps *data);
int		validate_wall(t_infoMaps *data);
void	free_info_maps(t_infoMaps *data);

/* Tracing Core */
void	init_game(t_infoMaps *data);
void	game(t_win *lmx);
int		init_textures(t_win *lmx);
int		close_window(t_win *lmx);
void	free_win(t_win *lmx);

/* Render & Raycast */
int		paint(void *lm);
void	draw_background(t_win *lmx);
void	draw_line(t_win *lmx, int x, int tex_x, t_tex *tex);
void	rays(t_win *lmx, int r, float ra, float ratan);
float	dist(float ax, float ay, float bx, float by);

/* Minimap */
void	m_paint(t_win *lmx);

/* Hooks & movement */
int		mouse_move(int x, int y, t_win *lmx);
int		key_press(int k_code, t_win *lmx);
int		key_release(int k_code, t_win *lmx);
void	movement(t_win *lmx, float strafe_dx, float strafe_dy);
void	limits(t_win *lmx);

#endif
