/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:28:14 by isang-yun         #+#    #+#             */
/*   Updated: 2024/01/24 12:41:22 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	g_worldmap[24][24];

void	clear_buffer(t_screen *s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
			s->buf[i][j] = 0;
	}
}

int	main_loop(t_screen *s)
{
	int		x;
	double	camerax;
	t_vec	raydir;
	t_vec	deltadist;
	//t_vec	sidedist;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	prep_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		lineheight;
	int		draw_start;
	int		draw_end;
	int		color;

	if (s->re_buf == 1)
		clear_buffer(s);
	x = 0;
	while (x < SCREEN_W)
	{
		hit = 0;
		camerax = 2 * x / (double)SCREEN_W - 1;
		raydir = vec_add(s->dir, vec_mul(s->plane, camerax));
		map_x = (int)s->pos.x;
		map_y = (int)s->pos.y;
		deltadist = vec_new(fabs(1 / raydir.x), fabs(1 / raydir.y));
		if (raydir.x < 0)
		{
			step_x = -1;
			sidedist_x = (s->pos.x - map_x) * deltadist.x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - s->pos.x) * deltadist.x;
		}
		if (raydir.y < 0)
		{
			step_y = -1;
			sidedist_y = (s->pos.y - map_y) * deltadist.y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - s->pos.y) * deltadist.y;
		}
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				map_x += step_x;
				sidedist_x += deltadist.x;
				side = 0;
			}
			else
			{
				map_y += step_y;
				sidedist_y += deltadist.y;
				side = 1;
			}
			if (g_worldmap[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			prep_wall_dist = (map_x - s->pos.x + (1 - step_x) / 2) / raydir.x;
		else
			prep_wall_dist = (map_y - s->pos.y + (1 - step_y) / 2) / raydir.y;
		lineheight = (int)(SCREEN_H / prep_wall_dist);
		draw_start = -lineheight / 2 + SCREEN_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = lineheight / 2 + SCREEN_H / 2;
		if (draw_end >= SCREEN_H)
			draw_end = SCREEN_H - 1;
		int	textnum = g_worldmap[map_x][map_y];
		// int	textnum = g_worldmap[map_x][map_y] - 1;
		double wall_x;
		if (side == 0)
			wall_x = s->pos.y + prep_wall_dist * raydir.y;
		else
			wall_x = s->pos.x + prep_wall_dist * raydir.x;
		wall_x -= floor(wall_x);
		int	text_x = (int)(wall_x * (double)TEX_W);
		if ((side == 0 && raydir.x > 0) || (side == 1 && raydir.y < 0))
			text_x = TEX_W - text_x - 1;
		double step = 1.0 * TEX_H / lineheight;
		//starting texture coordinate
		double text_pos = (draw_start - SCREEN_H / 2 + lineheight / 2) * step;
		int	y;
		y = draw_start;
		while (y < draw_end)
		{
			int	text_y = (int)text_pos & (TEX_H - 1);
			text_pos += step;
			color = s->texture[textnum][TEX_H * text_y + text_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			s->buf[y][x] = color;
			s->re_buf = 1;
			y++;
		}
		x++;
	}
	for(int y = 0; y < SCREEN_H; y++){
		for(int x = 0; x < SCREEN_W; x++)
			s->img.addr[y * SCREEN_W + x] = s->buf[y][x];
	}
	mlx_put_image_to_window(s->mlx, s->win, s->img.ptr, 0, 0);
	return (0);
}
