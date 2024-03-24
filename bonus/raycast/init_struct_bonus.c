/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:50 by isang-yun         #+#    #+#             */
/*   Updated: 2024/03/24 16:05:25 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	load_image(t_screen *s, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->ptr = mlx_xpm_file_to_image(s->mlx, path, &img->w, &img->h);
	if (!img->ptr)
	{
		perror(path);
		exit(1);
	}
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->size_line, &img->endian);
	y = -1;
	while (++y < img->h)
	{
		x = -1;
		while (++x < img->w)
			texture[img->w * y + x] = img->addr[img->w * y + x];
	}
	mlx_destroy_image(s->mlx, img->ptr);
}

static void	load_texture(t_screen *s)
{
	t_img	img;

	load_image(s, s->texture[0], s->map->west_texture, &img);
	load_image(s, s->texture[1], s->map->east_texture, &img);
	load_image(s, s->texture[2], s->map->north_texture, &img);
	load_image(s, s->texture[3], s->map->south_texture, &img);
	load_image(s, s->sub_texture[0], "textures/sans_1.xpm", &img);
	load_image(s, s->sub_texture[1], "textures/sans_2.xpm", &img);
	load_image(s, s->sub_texture[2], "textures/sans_3.xpm", &img);
	load_image(s, s->sub_texture[3], "textures/sans_4.xpm", &img);
}

static void	init_direction(t_screen *s)
{
	if (s->map->init_direction == 'N')
	{
		s->dir = vec_new(-1, 0);
		s->plane = vec_new(0, 1);
	}
	else if (s->map->init_direction == 'S')
	{
		s->dir = vec_new(1, 0);
		s->plane = vec_new(0, -1);
	}
	else if (s->map->init_direction == 'E')
	{
		s->dir = vec_new(0, 1);
		s->plane = vec_new(1, 0);
	}
	else
	{
		s->dir = vec_new(0, -1);
		s->plane = vec_new(-1, 0);
	}
}

static void	init_movekey(t_screen *s)
{
	s->move.key_a = 0;
	s->move.key_s = 0;
	s->move.key_w = 0;
	s->move.key_d = 0;
	s->move.key_arr_l = 0;
	s->move.key_arr_r = 0;
	s->pos = vec_new(
			s->map->map_start[0] + 0.1,
			s->map->map_start[1] + 0.1);
	s->movespeed = MOVESPEED;
	s->rotspeed = ROTSPEED;
	init_direction(s);
}

void	init_struct(t_screen *s, t_map *map)
{
	int	x;

	s->map = map;
	s->re_buf = 0;
	s->mouse_toggle = 0;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, SCREEN_W, SCREEN_H, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx, SCREEN_W, SCREEN_H);
	s->img.addr = (unsigned int *)mlx_get_data_addr(s->img.ptr,
			&s->img.bits_per_pixel, &s->img.size_line, &s->img.endian);
	s->buf = (int **)malloc(sizeof(int *) * SCREEN_H);
	x = -1;
	while (++x < SCREEN_H)
		s->buf[x] = (int *)malloc(sizeof(int) * SCREEN_W);
	s->texture = (int **)malloc(sizeof(int *) * TEX_NUM);
	x = -1;
	while (++x < TEX_NUM)
		s->texture[x] = (int *)malloc(sizeof(int) * (TEX_W * TEX_H));
	s->z_buffer = (double *)malloc(sizeof(double) * SCREEN_W);
	s->sub_texture = (int **)malloc(sizeof(int *) * 4);
	x = -1;
	while (++x < 4)
		s->sub_texture[x] = (int *)malloc(sizeof(int) * (TEX_W * TEX_H));
	load_texture(s);
	init_movekey(s);
}
