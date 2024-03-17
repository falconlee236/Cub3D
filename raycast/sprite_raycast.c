/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:22:18 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/17 19:25:19 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define SPRITE_NUM 19

struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

struct Sprite	sprite[SPRITE_NUM] =
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

void	sort_order(t_pair *orders)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < SPRITE_NUM)
	{
		j = 0;
		while (j < SPRITE_NUM - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(t_sprite_raycast_info *info)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair *)malloc(sizeof(t_pair) * SPRITE_NUM);
	if (!sprites)
		exit(0);
	i = 0;
	while (i < SPRITE_NUM)
	{
		sprites[i].first = info->sprite_dist[i];
		sprites[i].second = info->sprite_order[i];
		i++;
	}
	sort_order(sprites);
	i = 0;
	while (i < SPRITE_NUM)
	{
		info->sprite_dist[i] = sprites[SPRITE_NUM - i - 1].first;
		info->sprite_order[i] = sprites[SPRITE_NUM - i - 1].second;
		i++;
	}
	free(sprites);
}

int	set_sprite_raycast(t_screen *s, t_sprite_raycast_info *info)
{
	int	i;

	info->sprite_order = (int *)malloc(sizeof(int) * SPRITE_NUM);
	info->sprite_dist = (double *)malloc(sizeof(double) * SPRITE_NUM);
	if (!info->sprite_order || !info->sprite_dist)
		exit(0);
	i = 0;
	while (i < SPRITE_NUM)
	{
		info->sprite_order[i] = i;
		info->sprite_dist[i] = (
				(s->pos.x - sprite[i].x) * (s->pos.x - sprite[i].x)
				+ (s->pos.y - sprite[i].y) * (s->pos.y - sprite[i].y));
		i++;
	}
	sort_sprites(info);
	return (0);
}

void	det_sprite_raycast(t_screen *s, t_sprite_raycast_info *info, int i)
{
	double	det;
	t_vec	sprite_pos;

	sprite_pos.x = sprite[info->sprite_order[i]].x - s->pos.x;
	sprite_pos.y = sprite[info->sprite_order[i]].y - s->pos.y;
	det = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
	info->trans_pos.x = det * (
			s->dir.y * sprite_pos.x - s->dir.x * sprite_pos.y);
	info->trans_pos.y = det * (
			-s->plane.y * sprite_pos.x + s->plane.x * sprite_pos.y);
	info->sprite_screen_x = (int)((SCREEN_W / 2) * (
				1 + info->trans_pos.x / info->trans_pos.y));
}

void	cal_sprite_raycast(t_sprite_raycast_info *info)
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

// void	doing_innner_sprite_raycast()


void	doing_sprite_raycast(
	t_screen *s, t_sprite_raycast_info *info, int i)
{
	int		stripe;
	int		d;
	int		color;
	int		y;
	t_pos	text_cord;

	stripe = info->draw_start_x;
	while (stripe < info->draw_end_x)
	{
		text_cord.x = (int)((256 * (stripe - (-info->sprite_w / 2
							+ info->sprite_screen_x))
					* TEX_W / info->sprite_w) / 256);
		if (info->trans_pos.y > 0 && stripe > 0 && stripe < SCREEN_W
			&& info->trans_pos.y < s->z_buffer[stripe])
		{
			y = info->draw_start_y;
			while (y < info->draw_end_y)
			{
				d = (y - info->movescreen) * 256
					- SCREEN_H * 128 + info->sprite_h * 128;
				text_cord.y = ((d * TEX_H) / info->sprite_h) / 256;
				color = s->texture[sprite[info->sprite_order[i]].texture][
					TEX_W * text_cord.y + text_cord.x];
				if ((color & 0x00FFFFFF) != 0)
					s->buf[y][stripe] = color;
				y++;
			}
		}
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
