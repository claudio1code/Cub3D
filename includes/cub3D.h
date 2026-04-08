/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:17:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/08 19:54:46 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/X.h>
# include <math.h>

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

typedef struct s_libx
{
	float	xo;
	float	yo;
	float	rx;
	float	ry;
	float	pa;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	oldpy;
	float	oldpx;
	float	d_h;
	float	hx;
	float	hy;
	float	d_v;
	float	vx;
	float	vy;
	float	d_t;
	float	l_h;
	float	atan;
	int		ll;
	int		bpp;
	int		endian;
	int		matrix_s;
	int		w;
	int		a;
	int		s;
	int		d;
	int		last_mx;
	char	*addr;
	void	*lmx;
	void	*win;
	void	*img;
	float	**matrix;
	t_tex	tex[4];
}	t_win;

#endif