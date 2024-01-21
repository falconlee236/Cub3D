/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/21 20:26:33 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	g_worldmap[24][24] = {
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};


void	leak_check(void)
{
	system("leaks cub3D");
}

int	destory_hook_event(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(1);
}

t_pixel	**init_pixel(int w, int h, t_img *img)
{
	t_pixel	**pixel;
	int		x;
	int		y;

	pixel = (t_pixel **)malloc(sizeof(t_pixel *) * w);
	x = -1;
	while (++x < w)
	{
		pixel[x] = (t_pixel *)malloc(sizeof(t_pixel) * h);
		y = -1;
		while (++y < h)
		{
			pixel[x][y].dist = INF;
			pixel[x][y].color = (unsigned int *)((char *)img->addr
					+ img->size_line * y + img->bits_per_pixel / 8 * x);
		}
	}
	return (pixel);
}

void	init_struct(t_screen *s)
{
	s->w = 640;
	s->h = 480;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, s->w, s->h, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx, s->w, s->h);
	s->img.addr = (unsigned int *)mlx_get_data_addr(s->img.ptr,
			&(s->img.bits_per_pixel), &(s->img.size_line), &(s->img.endian));
	s->dist = (s->w / 2) * (1 / tan(FOV / 2));
	s->pixel = init_pixel(s->w, s->h, &s->img);
	//s->ray = (t_ray *)malloc(sizeof(t_ray) * s->w);
	s->pos = vec_new(12, 5);
	s->dir = vec_new(-1, 0);
	s->plane = vec_new(0, 0.66);
	s->movespeed = 0.05;
	s->rotspeed = 0.05;
	s->sin_unit = 0;
	s->cos_unit = 0;
}

void	ver_line(t_screen *s, int idx, int draw_start, int draw_end, int color)
{
	while (draw_start <= draw_end)
		mlx_pixel_put(s->mlx, s->win, idx, draw_start++, color);
}

int	main_loop(t_screen *s)
{
	int		idx;
	double	camerax;
	t_vec	raydir;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	prep_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		lineheight;
	int		draw_start;
	int		draw_end;
	int		color;

	idx = 0;
	while (idx < s->w)
	{
		hit = 0;
		camerax = 2 * idx / (double)s->w - 1;
		raydir = vec_add(s->dir, vec_mul(s->plane, camerax));
		map_x = (int)s->pos.x;
		map_y = (int)s->pos.y;
		deltadist_x = fabs(1 / raydir.x);
		deltadist_y = fabs(1 / raydir.y);
		if (raydir.x < 0)
		{
			step_x = -1;
			sidedist_x = (s->pos.x - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - s->pos.x) * deltadist_x;
		}
		if (raydir.y < 0)
		{
			step_y = -1;
			sidedist_y = (s->pos.y - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - s->pos.y) * deltadist_y;
		}
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				map_x += step_x;
				sidedist_x += deltadist_x;
				side = 0;
			}
			else
			{
				map_y += step_y;
				sidedist_y += deltadist_y;
				side = 1;
			}
			if (g_worldmap[map_x][map_y] > 0) hit = 1;
		}
		if (side == 0)
			prep_wall_dist = (map_x - s->pos.x + (1 - step_x) / 2) / raydir.x;
		else
			prep_wall_dist = (map_y - s->pos.y + (1 - step_y) / 2) / raydir.y;
		lineheight = (int)(s->h / prep_wall_dist);
		draw_start = -lineheight / 2 + s->h / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = lineheight / 2 + s->h / 2;
		if (draw_end >= s->h)
			draw_end = s->h - 1;
		if (g_worldmap[map_x][map_y] == 1)
			color = 0xFF0000;
		else if (g_worldmap[map_x][map_y] == 2)
			color = 0x00FF00;
		else if (g_worldmap[map_x][map_y] == 3)
			color = 0x0000FF;
		else if (g_worldmap[map_x][map_y] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		if (side == 1)
			color = color / 2;
		ver_line(s, idx, draw_start, draw_end, color);
		idx++;
	}
	mlx_clear_window(s->mlx, s->win);
	return (0);
}

int	key_hook_event(int key, t_screen *s)
{
	if (key == KEY_W)
	{
		if (!g_worldmap[(int)(s->pos.x + s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x += s->dir.x * s->movespeed;
		if (!g_worldmap[(int)(s->pos.x)][(int)(s->pos.y + s->dir.y * s->movespeed)])
			s->pos.y += s->dir.y * s->movespeed;
	}
	if (key == KEY_S)
	{
		if (!g_worldmap[(int)(s->pos.x - s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x -= s->dir.x * s->movespeed;
		if (!g_worldmap[(int)(s->pos.x)][(int)(s->pos.y - s->dir.y * s->movespeed)])
			s->pos.y -= s->dir.y * s->movespeed;
	}
	if (key == KEY_D)
	{
		s->dir = vec_rot(s->dir, -1);
		s->plane = vec_rot(s->plane, -1);
	}
	if (key == KEY_A)
	{
		s->dir = vec_rot(s->dir, 1);
		s->plane = vec_rot(s->plane, 1);
	}
	if (key == KEY_ESC)
		exit(0);
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
	mlx_hook(s.win, X_EVENT_KEY_PRESS, 0, &key_hook_event, &s);
	mlx_loop(s.mlx);
	return (0);
}
