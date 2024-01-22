/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/22 19:23:29 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define texWidth 64
#define texHeight 64

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

void	load_image(t_screen *s, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->ptr = mlx_xpm_file_to_image(s->mlx, path, &img->w, &img->h);
	img->addr = (unsigned int*)mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->size_line, &img->endian);
	y = -1;
	while (++y < img->h)
	{
		x = -1;
		while (++x < img->w)
			texture[img->w * y + x] = img->addr[img->w * y + x];
	}
	mlx_destroy_image(s->mlx, img->ptr);
}

void	load_texture(t_screen *s)
{
	t_img	img;

	load_image(s, s->texture[0], "textures/eagle.xpm", &img);
	load_image(s, s->texture[1], "textures/redbrick.xpm", &img);
	load_image(s, s->texture[2], "textures/purplestone.xpm", &img);
	load_image(s, s->texture[3], "textures/greystone.xpm", &img);
	load_image(s, s->texture[4], "textures/bluestone.xpm", &img);
	load_image(s, s->texture[5], "textures/mossy.xpm", &img);
	load_image(s, s->texture[6], "textures/wood.xpm", &img);
	load_image(s, s->texture[7], "textures/colorstone.xpm", &img);
}

void	init_struct(t_screen *s)
{
	int	x;

	x = -1;
	s->w = 1280;
	s->h = 760;
	s->re_buf = 0;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, s->w, s->h, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx, s->w, s->h);
	s->img.addr = (unsigned int*)mlx_get_data_addr(s->img.ptr, &s->img.bits_per_pixel, &s->img.size_line, &s->img.endian);
	s->buf = (int **)malloc(sizeof(int *) * (s->h));
	while (++x < s->h)
		s->buf[x] = (int *)malloc(sizeof(int) * (s->w));
	s->texture = (int **)malloc(sizeof(int *) * 8);
	x = -1;
	while (++x < 8)
		s->texture[x] = (int *)malloc(sizeof(int) * (texWidth * texHeight));
	load_texture(s);
	s->pos = vec_new(22, 11.5);
	s->dir = vec_new(-1, 0);
	s->plane = vec_new(0, 0.66);
	s->movespeed = 0.1;
	s->rotspeed = 5;
}

int	main_loop(t_screen *s)
{
	int		x;
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
	int		i;
	int		j;

	x = 0;
	if (s->re_buf == 1)
	{
		i = -1;
		while (++i < s->h)
		{
			j = -1;
			while (++j < s->w)
				s->buf[i][j] = 0;
		}
	}
	while (x < s->w)
	{
		hit = 0;
		camerax = 2 * x / (double)s->w - 1;
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
		int	textnum = g_worldmap[map_x][map_y];
		// int	textnum = g_worldmap[map_x][map_y] - 1;
		double wall_x;
		if (side == 0)
			wall_x = s->pos.y + prep_wall_dist * raydir.y;
		else
			wall_x = s->pos.x + prep_wall_dist * raydir.x;
		wall_x -= floor(wall_x);
		int	text_x = (int)(wall_x * (double)texWidth);
		if ((side == 0 && raydir.x > 0) || (side == 1 && raydir.y < 0))
			text_x = texWidth - text_x - 1;
		double step = 1.0 * texHeight / lineheight;
		//starting texture coordinate
		double text_pos = (draw_start - s->h / 2 + lineheight / 2) * step;
		int	y;
		y = draw_start;
		while (y < draw_end)
		{
			int	text_y = (int)text_pos & (texHeight - 1);
			text_pos += step;
			color = s->texture[textnum][texHeight * text_y + text_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			s->buf[y][x] = color;
			s->re_buf = 1;
			y++;
		}
		x++;
	}
	for(int y = 0; y < s->h; y++){
		for(int x = 0; x < s->w; x++)
			s->img.addr[y * s->w + x] = s->buf[y][x];
	}
	mlx_put_image_to_window(s->mlx, s->win, s->img.ptr, 0, 0);
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
