/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:53:16 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/24 15:17:32 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_order(t_screen *s, t_pair *orders)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < s->map->sprite_cnt)
	{
		j = 0;
		while (j < s->map->sprite_cnt - 1)
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

void	sort_sprites(t_screen *s, t_sprite_raycast_info *info)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair *)malloc(sizeof(t_pair) * s->map->sprite_cnt);
	if (!sprites)
		exit(0);
	i = 0;
	while (i < s->map->sprite_cnt)
	{
		sprites[i].first = info->sprite_dist[i];
		sprites[i].second = info->sprite_order[i];
		i++;
	}
	sort_order(s, sprites);
	i = 0;
	while (i < s->map->sprite_cnt)
	{
		info->sprite_dist[i] = sprites[s->map->sprite_cnt - i - 1].first;
		info->sprite_order[i] = sprites[s->map->sprite_cnt - i - 1].second;
		i++;
	}
	free(sprites);
}

int	set_sprite_raycast(t_screen *s, t_sprite_raycast_info *info)
{
	int	i;

	info->sprite_order = (int *)malloc(sizeof(int) * s->map->sprite_cnt);
	info->sprite_dist = (double *)malloc(sizeof(double) * s->map->sprite_cnt);
	if (!info->sprite_order || !info->sprite_dist)
		exit(0);
	i = 0;
	while (i < s->map->sprite_cnt)
	{
		info->sprite_order[i] = i;
		info->sprite_dist[i] = (
				(s->pos.x - s->map->sprite_pos[i].x) 
				* (s->pos.x - s->map->sprite_pos[i].x)
				+ (s->pos.y - s->map->sprite_pos[i].y)
				* (s->pos.y - s->map->sprite_pos[i].y));
		i++;
	}
	sort_sprites(s, info);
	return (0);
}

void	det_sprite_raycast(t_screen *s, t_sprite_raycast_info *info, int i)
{
	double	det;
	t_vec	sprite_pos;

	sprite_pos.x = s->map->sprite_pos[info->sprite_order[i]].x - s->pos.x;
	sprite_pos.y = s->map->sprite_pos[info->sprite_order[i]].y - s->pos.y;
	det = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
	info->trans_pos.x = det * (
			s->dir.y * sprite_pos.x - s->dir.x * sprite_pos.y);
	info->trans_pos.y = det * (
			-s->plane.y * sprite_pos.x + s->plane.x * sprite_pos.y);
	info->sprite_screen_x = (int)((SCREEN_W / 2) * (
				1 + info->trans_pos.x / info->trans_pos.y));
}
