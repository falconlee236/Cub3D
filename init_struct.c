/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:50 by isang-yun         #+#    #+#             */
/*   Updated: 2024/03/07 17:19:58 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_image(t_screen *s, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->ptr = mlx_xpm_file_to_image(s->mlx, path, &img->w, &img->h);
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
	s->re_buf = 0;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, SCREEN_W, SCREEN_H, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx, SCREEN_W, SCREEN_H);
	s->img.addr = (unsigned int *)mlx_get_data_addr(s->img.ptr, 
			&s->img.bits_per_pixel, &s->img.size_line, &s->img.endian);
	s->buf = (int **)malloc(sizeof(int *) * SCREEN_H);
	while (++x < SCREEN_H)
		s->buf[x] = (int *)malloc(sizeof(int) * SCREEN_W);
	s->texture = (int **)malloc(sizeof(int *) * 8);
	x = -1;
	while (++x < 8)
		s->texture[x] = (int *)malloc(sizeof(int) * (TEX_W * TEX_H));
	load_texture(s);
	s->pos = vec_new(22, 11.5);
	s->dir = vec_new(-1, 0);
	s->plane = vec_new(0, 0.66);
	s->movespeed = MOVESPEED;
	s->rotspeed = ROTSPEED;
}
