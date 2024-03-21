/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:23:36 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/21 19:35:19 by yonyoo           ###   ########seoul.kr  */
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
# define MOVE 0.5
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

//SECTION - Sprite Sturct
# define SPRITE_NUM 19

typedef struct s_sprite
{
	double		x;
	double		y;
	int			texture;
}	t_sprite;

typedef struct s_pair{
	double	first;
	int		second;
}	t_pair;
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

//SECTION - sprite ray casting struct
typedef struct s_sprite_raycast_info{
	int		*sprite_order;
	double	*sprite_dist;
	int		movescreen;
	int		sprite_screen_x;
	int		sprite_h;
	int		sprite_w;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	t_vec	trans_pos;
	t_pos	text_cord;
}	t_sprite_raycast_info;
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
	int		*sprite_texture;
	int		**sub_texture;
	double	*z_buffer;
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
	int		ceiling_color;
	int		floor_color;
	char	*east_texture;
	char	*west_texture;
	char	*north_texture;
	char	*south_texture;
	char	init_direction;
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

//ANCHOR - sprite raycast function
void	sprite_raycast(t_screen *s);
void	sort_order(t_pair *orders);
void	sort_sprites(t_sprite_raycast_info *info);
int		set_sprite_raycast(t_screen *s, t_sprite_raycast_info *info);
void	det_sprite_raycast(t_screen *s, t_sprite_raycast_info *info, int i);

//ANCHOR - minimap render function
void	render_minimap(t_screen *s);

//ANCHOR - player move function
void	move_front_back(t_screen *s);
void	move_left_right(t_screen *s);
void	rot_left_right(t_screen *s);

int		ft_strcmp(const char *s1, const char *s2);
void	exit_error(char *str);
void	free_str_arr(char **arr, char *str);

#endif
