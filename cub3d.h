/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:23:36 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/17 17:18:54 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include "./parse/parse.h"

//SECTION - KEY MACRO
# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_MOUSE_MOVE			6
# define ON_DESTROY 				17
# define KEY_ESC					53
# define KEY_W						13
# define KEY_A						0
# define KEY_S						1
# define KEY_D						2
# define KEY_AR_L 					123
# define KEY_AR_R 					124
# define KEY_1						18
# define KEY_2						19
//!SECTION

//SECTION - PIXEL SIZE CONST
# define TEX_W 64
# define TEX_H 64
# define SCREEN_W 1280
# define SCREEN_H 760
//!SECTION

//SECTION - Game Play Parameter
# define MOVESPEED 0.05
# define ROTSPEED 3
//!SECTION

//SECTION - Map Parameter
# define MINI_SCALE 0.25
# define TILE_SIZE 60
# define MAP_NUM_ROWS 10
# define MAP_NUM_COLS 10
//!SECTION

//SECTION Vector operation
# define PI 3.14159265

typedef struct s_vec{
	double	x;
	double	y;
}	t_vec;
//!SECTION

//SECTION - POS struct (integer vector)
typedef struct s_pos{
	int	x;
	int	y;
}	t_pos;
//!SECTION

//SECTION - wall Ray casting struct
typedef struct s_vert_raycast_info{
	t_vec	raydir;
	t_vec	deltadist;
	t_vec	sidedist;
	t_pos	map_pos;
	t_pos	step_size;
	double	prep_wall_dist;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
	int		text_x;
	double	step;
	double	text_pos;
}	t_vert_raycast_info;
//!SECTION

//SECTION - floor, celling ray casting struct
typedef struct s_hori_raycast_info{
	t_vec	floor_step;
	t_vec	floor_cord;
}	t_hori_raycast_info;
//!SECTION

//SECTION - key move struct
typedef struct s_move{
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_w;
	int	key_arr_l;
	int	key_arr_r;
}	t_move;
//!SECTION

typedef struct s_img{
	int				w;
	int				h;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	void			*ptr;
	unsigned int	*addr;
}	t_img;

typedef struct s_screen{
	void	*mlx;
	void	*win;
	int		**buf;
	int		**texture;
	double	movespeed;
	double	rotspeed;
	int		re_buf;
	int		mouse_toggle;
	t_move	move;
	t_img	img;
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_screen;
//!SECTION

typedef struct s_map{
	int		**map;
	size_t	max_height;
	size_t	max_width;
}	t_map;

//ANCHOR - Vector operation
t_vec	vec_new(double x, double y);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, double c);
t_vec	get_dir_vec(t_vec a, t_vec b, double x, double y);
t_vec	vec_rot(t_vec a, int theta);

//ANCHOR - hook event
int		key_hook_event(t_screen *s);
int		destory_hook_event(t_screen *s);
int		key_press(int key, t_screen *s);
int		key_release(int key, t_screen *s);
int		mouse_hook_event(int x, int y, t_screen *s);

//ANCHOR - Init struct
void	init_struct(t_screen *s);

//ANCHOR - main loop
int		main_loop(t_screen *s);

//ANCHOR - raycast util function
void	clear_buffer(t_screen *s);
t_pos	pos_new(int x, int y);
void	switch_buffer(t_screen *s);
int		create_trgb(int t, int r, int g, int b);

//ANCHOR - horiontal raycast function
void	horizontal_raycast(t_screen *s);

//ANCHOR - vertical raycast function
void	vertical_raycast(t_screen *s);

//ANCHOR - minimap render function
void	render_minimap(t_screen *s);

//ANCHOR - player move function
void	move_front_back(t_screen *s);
void	move_left_right(t_screen *s);
void	rot_left_right(t_screen *s);
#endif
