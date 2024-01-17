/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:23:36 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/17 15:59:27 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# define PI 3.14159265

//SECTION Vector struct
typedef struct s_vec{
	double	x;
	double	y;
}	t_vec;

typedef struct s_img{
	int				w;
	int				h;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	void			*ptr;
	unsigned int	*addr;
}	t_img;

typedef struct s_pixel{
	double			dist;
	unsigned int	*color;
}	t_pixel;

typedef struct s_ray{
	t_vec	dir;
	double	dist;
}	t_ray;

typedef struct s_screen{
	void	*mlx;
	void	*win;
	t_pixel	**pixel;
	int		w;
	int		h;
	double	sin_unit;
	double	cos_unit;
	double	dist;
	t_ray	*ray;
	t_img	img;
	t_vec	origin;
	t_vec	dir;
	t_vec	plane;
}	t_screen;
#endif