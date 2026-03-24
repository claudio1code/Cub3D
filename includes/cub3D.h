/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:17:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/24 08:51:16 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <math.h>
# include <X11/X.h>

typedef struct s_libx
{
	int				ll;
	int				px;
	int				py;
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