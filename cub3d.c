/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/10 18:26:08 by sangylee         ###   ########.fr       */
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

void	fill_squres(t_img *map, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)(MINI_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINI_SCALE * TILE_SIZE))
		{
			map->addr[(int)(MINI_SCALE * SCREEN_W) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_screen *s)
{
	int			x;
	int			end_x;
	int			y;
	int			end_y;
	t_img		map;

	map.ptr = mlx_new_image(
			s->mlx, (int)(MINI_SCALE * SCREEN_W), (int)(MINI_SCALE * SCREEN_H));
	map.addr = (unsigned int *)mlx_get_data_addr(map.ptr,
			&(map.bits_per_pixel), &(map.size_line), &(map.endian));
	if ((int)s->pos.x - MAP_NUM_ROWS / 2 < 0)
		x = 0;
	else
		x = (int)s->pos.x - MAP_NUM_ROWS / 2;
	if ((int)s->pos.x + MAP_NUM_ROWS / 2 >= 24)
		end_x = 23;
	else
		end_x = (int)s->pos.x + MAP_NUM_ROWS / 2;
	while (x < end_x)
	{
		if ((int)s->pos.y - MAP_NUM_COLS / 2 < 0)
			y = 0;
		else
			y = (int)s->pos.y - MAP_NUM_COLS / 2;
		if ((int)s->pos.y + MAP_NUM_COLS / 2 >= 24)
			end_y = 23;
		else
			end_y = (int)s->pos.y + MAP_NUM_COLS / 2;
		while (y < end_y)
		{
			printf("%d %d %d\n", (int)s->pos.x, x, y);
			if (g_worldmap[x][y])
				fill_squres(&map, (int)(MINI_SCALE * TILE_SIZE * y),
					(int)(MINI_SCALE * TILE_SIZE * x), 0x000000);
			else
				fill_squres(&map, (int)(MINI_SCALE * TILE_SIZE * y),
					(int)(MINI_SCALE * TILE_SIZE * x), 0xffffff);
			if (x == (int)s->pos.x && y == (int)s->pos.y)
				fill_squres(&map, (int)(MINI_SCALE * TILE_SIZE * y),
					(int)(MINI_SCALE * TILE_SIZE * x), 0xff0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(s->mlx, s->win, map.ptr,
		(int)(SCREEN_W * (1 - MINI_SCALE)), (int)(SCREEN_H * (1 - MINI_SCALE)));
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
	mlx_loop_hook(s.mlx, &main_loop, &s);
	mlx_hook(s.win, ON_DESTROY, 0, &destory_hook_event, &s);
	mlx_hook(s.win, X_EVENT_KEY_PRESS, 0, &key_press, &s);
	mlx_hook(s.win, X_EVENT_KEY_RELEASE, 0, &key_release, &s);
	mlx_hook(s.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook_event, &s);
	mlx_loop(s.mlx);
	return (0);
}
