/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftlurker <ftlurker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:17:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/04 16:17:06 by ftlurker         ###   ########.fr       */
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
# define DR 0.0174533

typedef struct s_libx
{
	float			rx;
	float			ry;
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

#endif