/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:31:21 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/10 14:18:01 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_horizontal_raycast(
	t_screen *s, t_hori_raycast_info *info, int y)
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
	row_dist = vertial_camera_pos / cur_ypos;
	info->floor_step.x = row_dist * (end_raydir.x - start_raydir.x) / SCREEN_W;
	info->floor_step.y = row_dist * (end_raydir.y - start_raydir.y) / SCREEN_W;
	info->floor_cord = vec_add(s->pos, vec_mul(start_raydir, row_dist));
}

static void	doing_horizontal_raycast(t_screen *s, t_hori_raycast_info *info,
	int x, int y)
{
	t_pos	cell_cord;
	t_pos	tex_cord;
	int		floor_idx;
	int		cell_idx;
	int		color;

	cell_cord.x = (int)(info->floor_cord.x);
	cell_cord.y = (int)(info->floor_cord.y);
	tex_cord.x = (int)(TEX_W * (info->floor_cord.x - cell_cord.x))
		& (TEX_W - 1);
	tex_cord.y = (int)(TEX_H * (info->floor_cord.y - cell_cord.y))
		& (TEX_H - 1);
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
