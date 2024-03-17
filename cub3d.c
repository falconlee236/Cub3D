/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/17 16:31:10 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	g_worldmap[24][24] = {
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

void	leak_check(void)
{
	system("leaks cub3D");
}

void	fill_squres(t_img *m_map, int x, int y, int color)
{
	int	i;
	int	j;
	int	idx;

	j = 0;
	idx = MINI_SCALE * SCREEN_W;
	while (j < (int)(MINI_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINI_SCALE * TILE_SIZE))
		{
			m_map->addr[idx * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	cord_convert(t_screen *s, int x, int y, t_pos *conv_cord)
{
	if ((int)s->pos.x - MAP_NUM_ROWS / 2 + x < 0)
		conv_cord->x = 0;
	else if ((int)s->pos.x - MAP_NUM_ROWS / 2 + x >= 24)
		conv_cord->x = 23;
	else
		conv_cord->x = (int)s->pos.x - MAP_NUM_ROWS / 2 + x;
	if ((int)s->pos.y - MAP_NUM_COLS / 2 + y < 0)
		conv_cord->y = 0;
	else if ((int)s->pos.y - MAP_NUM_COLS / 2 + y >= 24)
		conv_cord->y = 23;
	else
		conv_cord->y = (int)s->pos.y - MAP_NUM_COLS / 2 + y;
}

void	decide_color_and_drawing(
	t_screen *s, t_img m_map, t_pos conv_cord, t_pos cord)
{
	if (g_worldmap[conv_cord.x][conv_cord.y])
		fill_squres(&m_map, (int)(MINI_SCALE * TILE_SIZE * cord.y),
			(int)(MINI_SCALE * TILE_SIZE * cord.x), 0x000000);
	else
		fill_squres(&m_map, (int)(MINI_SCALE * TILE_SIZE * cord.y),
			(int)(MINI_SCALE * TILE_SIZE * cord.x), 0xffffff);
	if (conv_cord.x == (int)s->pos.x && conv_cord.y == (int)s->pos.y)
		fill_squres(&m_map, (int)(MINI_SCALE * TILE_SIZE * cord.y),
			(int)(MINI_SCALE * TILE_SIZE * cord.x), 0xff0000);
}

void	render_map(t_screen *s)
{
	t_img		m_map;
	t_pos		conv_cord;
	t_pos		cord;

	m_map.ptr = mlx_new_image(
			s->mlx, (int)(MINI_SCALE * SCREEN_W), (int)(MINI_SCALE * SCREEN_H));
	m_map.addr = (unsigned int *)mlx_get_data_addr(m_map.ptr,
			&(m_map.bits_per_pixel), &(m_map.size_line), &(m_map.endian));
	cord.x = 0;
	while (cord.x < MAP_NUM_ROWS)
	{
		cord.y = 0;
		while (cord.y < MAP_NUM_COLS)
		{
			cord_convert(s, cord.x, cord.y, &conv_cord);
			decide_color_and_drawing(s, m_map, conv_cord, cord);
			cord.y++;
		}
		cord.x++;
	}
	mlx_put_image_to_window(s->mlx, s->win, m_map.ptr,
		(int)(SCREEN_W * (1.11 - MINI_SCALE)),
		(int)(SCREEN_H * (1.11 - MINI_SCALE)));
}

int	main_loop(t_screen *s)
{
	int					x;
	double				camera_x;
	t_vert_raycast_info	info;

	if (s->re_buf == 1)
		clear_buffer(s);
	horizontal_raycast(s);
	x = 0;
	while (x < SCREEN_W)
	{
		info.hit = 0;
		camera_x = 2 * x / (double)SCREEN_W - 1;
		info.raydir = vec_add(s->dir, vec_mul(s->plane, camera_x));
		info.map_pos = pos_new((int)s->pos.x, (int)s->pos.y);
		info.deltadist = vec_new(
				fabs(1 / info.raydir.x), fabs(1 / info.raydir.y));
		init_vertical_raycast(s, &info);
		doing_vertical_raycast(s, &info);
		set_vertical_raycastinfo(s, &info);
		drawing_vertical_raycast(s, &info, x);
		x++;
	}
	switch_buffer(s);
	render_map(s);
	key_hook_event(s);
	return (0);
}


//LINK - Main.c
int	main(void)
{
	t_screen	s;

	atexit(leak_check);
	init_struct(&s);
	s.move.key_a = 0;
	s.move.key_s = 0;
	s.move.key_w = 0;
	s.move.key_d = 0;
	s.move.key_arr_l = 0;
	s.move.key_arr_r = 0;
	mlx_loop_hook(s.mlx, &main_loop, &s);
	mlx_hook(s.win, ON_DESTROY, 0, &destory_hook_event, &s);
	mlx_hook(s.win, X_EVENT_KEY_PRESS, 0, &key_press, &s);
	mlx_hook(s.win, X_EVENT_KEY_RELEASE, 0, &key_release, &s);
	mlx_hook(s.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook_event, &s);
	mlx_loop(s.mlx);
	return (0);
}