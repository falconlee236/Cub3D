/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:53:16 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/17 21:14:03 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_sprite	g_sprite[SPRITE_NUM];

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
				(s->pos.x - g_sprite[i].x) * (s->pos.x - g_sprite[i].x)
				+ (s->pos.y - g_sprite[i].y) * (s->pos.y - g_sprite[i].y));
		i++;
	}
	sort_sprites(info);
	return (0);
}

void	det_sprite_raycast(t_screen *s, t_sprite_raycast_info *info, int i)
{
	double	det;
	t_vec	sprite_pos;

	sprite_pos.x = g_sprite[info->sprite_order[i]].x - s->pos.x;
	sprite_pos.y = g_sprite[info->sprite_order[i]].y - s->pos.y;
	det = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
	info->trans_pos.x = det * (
			s->dir.y * sprite_pos.x - s->dir.x * sprite_pos.y);
	info->trans_pos.y = det * (
			-s->plane.y * sprite_pos.x + s->plane.x * sprite_pos.y);
	info->sprite_screen_x = (int)((SCREEN_W / 2) * (
				1 + info->trans_pos.x / info->trans_pos.y));
}
