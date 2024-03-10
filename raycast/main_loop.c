/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:28:14 by isang-yun         #+#    #+#             */
/*   Updated: 2024/03/10 12:31:46 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern int	g_worldmap[24][24];

static void	init_raycast(t_screen *s, t_vert_raycast_info *info)
{
	if (info->raydir.x < 0)
	{
		info->step_size.x = -1;
		info->sidedist.x = (s->pos.x - info->map_pos.x) * info->deltadist.x;
	}
	else
	{
		info->step_size.x = 1;
		info->sidedist.x = (
				info->map_pos.x + 1.0 - s->pos.x) * info->deltadist.x;
	}
	if (info->raydir.y < 0)
	{
		info->step_size.y = -1;
		info->sidedist.y = (s->pos.y - info->map_pos.y) * info->deltadist.y;
	}
	else
	{
		info->step_size.y = 1;
		info->sidedist.y = (
				info->map_pos.y + 1.0 - s->pos.y) * info->deltadist.y;
	}
}

static void	doing_raycast(t_screen *s, t_vert_raycast_info *info)
{
	while (info->hit == 0)
	{
		if (info->sidedist.x < info->sidedist.y)
		{
			info->map_pos.x += info->step_size.x;
			info->sidedist.x += info->deltadist.x;
			info->side = 0;
		}
		else
		{
			info->map_pos.y += info->step_size.y;
			info->sidedist.y += info->deltadist.y;
			info->side = 1;
		}
		if (g_worldmap[info->map_pos.x][info->map_pos.y] > 0)
			info->hit = 1;
	}
	if (info->side == 0)
		info->prep_wall_dist = (info->map_pos.x - s->pos.x + (
					1 - info->step_size.x) / 2) / info->raydir.x;
	else
		info->prep_wall_dist = (info->map_pos.y - s->pos.y + (
					1 - info->step_size.y) / 2) / info->raydir.y;
}

static void	set_raycastinfo(t_screen *s, t_vert_raycast_info *info)
{
	int		lineheight;
	double	wall_x;

	lineheight = (int)(SCREEN_H / info->prep_wall_dist);
	info->draw_start = -lineheight / 2 + SCREEN_H / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = lineheight / 2 + SCREEN_H / 2;
	if (info->draw_end >= SCREEN_H)
		info->draw_end = SCREEN_H - 1;
	if (info->side == 0)
		wall_x = s->pos.y + info->prep_wall_dist * info->raydir.y;
	else
		wall_x = s->pos.x + info->prep_wall_dist * info->raydir.x;
	wall_x -= floor(wall_x);
	info->text_x = (int)(wall_x * (double)TEX_W);
	if ((info->side == 0 && info->raydir.x > 0)
		|| (info->side == 1 && info->raydir.y < 0))
		info->text_x = TEX_W - info->text_x - 1;
	info->step = 1.0 * TEX_H / lineheight;
	info->text_pos = (info->draw_start - SCREEN_H / 2 + lineheight / 2)
		* info->step;
}

// int	textnum = g_worldmap[info.map_pos.x][info.map_pos.y] - 1;
static void	drawing_raycast(t_screen *s, t_vert_raycast_info *info, int x)
{
	int	y;
	int	textnum;
	int	text_y;
	int	color;

	y = info->draw_start;
	textnum = g_worldmap[info->map_pos.x][info->map_pos.y];
	while (y < info->draw_end)
	{
		text_y = (int)(info->text_pos) & (TEX_H - 1);
		info->text_pos += info->step;
		color = s->texture[textnum][TEX_H * text_y + info->text_x];
		if (info->side == 1)
			color = (color >> 1) & 8355711;
		s->buf[y][x] = color;
		s->re_buf = 1;
		y++;
	}
}

void	init_horizontal_raycast(t_screen *s, t_hori_raycast_info *info, int y)
{
	t_vec	start_raydir;
	t_vec	end_raydir;
	float	row_dist;
	int		cur_ypos;
	float	vertial_camera_pos;

	start_raydir = vec_sub(s->dir, s->plane);
	end_raydir = vec_add(s->dir, s->plane);
	cur_ypos = y - SCREEN_H / 2;
	vertial_camera_pos = 0.5 * SCREEN_H;
	row_dist = cur_ypos / vertial_camera_pos;
	info->floor_step = vec_mul(
			vec_mul(vec_sub(end_raydir, start_raydir), row_dist), 1 / SCREEN_W);
	info->floor_cord = vec_add(s->pos, vec_mul(start_raydir, row_dist));
}

void	doing_horizontal_raycast(t_screen *s, t_hori_raycast_info *info,
	int x, int y)
{
	t_pos	cell_cord;
	t_pos	tex_cord;
	int		floor_idx;
	int		cell_idx;
	int		color;

	cell_cord.x = (int)info->floor_cord.x;
	cell_cord.y = (int)info->floor_cord.y;
	tex_cord.x = (int)(TEX_W * info->floor_cord.x - cell_cord.x) & (TEX_W - 1);
	tex_cord.y = (int)(TEX_H * info->floor_cord.y - cell_cord.y) & (TEX_H - 1);
	info->floor_cord = vec_add(info->floor_cord, info->floor_step);
	floor_idx = 3;
	cell_idx = 6;
	color = s->texture[floor_idx][TEX_W * tex_cord.y + tex_cord.x];
	color = (color >> 1) & 8355711;
	s->buf[y][x] = color;
	color = s->texture[cell_idx][TEX_W * tex_cord.y + tex_cord.x];
	color = (color >> 1) & 8355711;
	s->buf[SCREEN_H - y - 1][x] = color;
}

void	horizontal_raycast(t_screen *s)
{
	int					x;
	int					y;
	t_hori_raycast_info	info;

	y = 0;
	while (y < SCREEN_H)
	{
		init_horizontal_raycast(s, &info, y);
		x = 0;
		while (x < SCREEN_W)
		{
			doing_horizontal_raycast(s, &info, x, y);
			x++;
		}
		y++;
	}
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
		init_raycast(s, &info);
		doing_raycast(s, &info);
		set_raycastinfo(s, &info);
		drawing_raycast(s, &info, x);
		x++;
	}
	switch_buffer(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img.ptr, 0, 0);
	return (0);
}
