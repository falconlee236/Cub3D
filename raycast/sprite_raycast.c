/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:22:18 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/17 21:13:17 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite	g_sprite[SPRITE_NUM] =
{		
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

static void	cal_sprite_raycast(t_sprite_raycast_info *info)
{
	info->movescreen = (int)(MOVE / info->trans_pos.y);
	info->sprite_h = (int)fabs((SCREEN_H / info->trans_pos.y));
	info->draw_start_y = -info->sprite_h / 2 + SCREEN_H / 2
		+ info->movescreen;
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->sprite_h / 2 + SCREEN_H / 2
		+ info->movescreen;
	if (info->draw_end_y >= SCREEN_H)
		info->draw_end_y = SCREEN_H - 1;
	info->sprite_w = (int)fabs((SCREEN_H / info->trans_pos.y));
	info->draw_start_x = -info->sprite_w / 2 + info->sprite_screen_x;
	if (info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->sprite_w / 2 + info->sprite_screen_x;
	if (info->draw_end_x >= SCREEN_W)
		info->draw_end_x = SCREEN_W - 1;
}

static void	doing_innner_sprite_raycast(
	t_screen *s, t_sprite_raycast_info *info, int i, int stripe)
{
	int		y;
	int		d;
	int		color;

	y = info->draw_start_y;
	while (y < info->draw_end_y)
	{
		d = (y - info->movescreen) * 256
			- SCREEN_H * 128 + info->sprite_h * 128;
		info->text_cord.y = ((d * TEX_H) / info->sprite_h) / 256;
		color = s->texture[g_sprite[info->sprite_order[i]].texture][
			TEX_W * info->text_cord.y + info->text_cord.x];
		if ((color & 0x00FFFFFF) != 0)
			s->buf[y][stripe] = color;
		y++;
	}
}

static void	doing_sprite_raycast(
	t_screen *s, t_sprite_raycast_info *info, int i)
{
	int		stripe;

	stripe = info->draw_start_x;
	while (stripe < info->draw_end_x)
	{
		info->text_cord.x = (int)((256 * (stripe - (-info->sprite_w / 2
							+ info->sprite_screen_x))
					* TEX_W / info->sprite_w) / 256);
		if (info->trans_pos.y > 0 && stripe > 0 && stripe < SCREEN_W
			&& info->trans_pos.y < s->z_buffer[stripe])
			doing_innner_sprite_raycast(s, info, i, stripe);
		stripe++;
	}
}

void	sprite_raycast(t_screen *s)
{
	int						i;
	t_sprite_raycast_info	info;

	set_sprite_raycast(s, &info);
	i = 0;
	while (i < SPRITE_NUM)
	{
		det_sprite_raycast(s, &info, i);
		cal_sprite_raycast(&info);
		doing_sprite_raycast(s, &info, i);
		i++;
	}
	free(info.sprite_order);
	free(info.sprite_dist);
}
