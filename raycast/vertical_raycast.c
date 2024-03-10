/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:28:14 by isang-yun         #+#    #+#             */
/*   Updated: 2024/03/10 12:41:43 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern int	g_worldmap[24][24];

void	init_vertical_raycast(t_screen *s, t_vert_raycast_info *info)
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

void	doing_vertical_raycast(t_screen *s, t_vert_raycast_info *info)
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

void	set_vertical_raycastinfo(t_screen *s, t_vert_raycast_info *info)
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
void	drawing_vertical_raycast(t_screen *s, t_vert_raycast_info *info, int x)
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
