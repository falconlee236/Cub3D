/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:23:36 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/20 17:03:09 by sangylee         ###   ########.fr       */
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
# define FOV -0.5
# define INF 1.7976931348623157E+308
# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define ON_DESTROY 				17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

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
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	double	movespeed;
	double	rotspeed;
}	t_screen;

//ANCHOR - Vector operation
t_vec	vec_new(double x, double y);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, double c);
t_vec	get_dir_vec(t_vec a, t_vec b, double x, double y);
t_vec	vec_rot(t_vec a, int theta);
#endif