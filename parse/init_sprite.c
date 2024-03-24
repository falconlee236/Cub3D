/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 05:09:22 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 15:08:32 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_valid(int x, int y, t_map *map)
{
	if (x < 0 || x >= map->max_height
		|| y < 0 || y >= map->max_width
		|| map->map[x][y] == 1)
		return (0);
	return (1);
}

static void	add_sprite(int x, int y, t_map *map)
{
	map->sprite_pos[map->sprite_cnt].x = x;
	map->sprite_pos[map->sprite_cnt].y = y;
	(map->sprite_cnt)++;
}

void	init_sprite(t_map *map)
{
	if (map->map_start[0] >= 1 && map->map_start[0] < map->max_height - 1
		&& map->map_start[1] >= 1 && map->map_start[1] < map->max_width - 1)
	{
		if (is_valid(map->map_start[0], map->map_start[1] - 1, map))
			add_sprite(map->map_start[0], map->map_start[1] - 1, map);
		if (is_valid(map->map_start[0], map->map_start[1] + 1, map))
			add_sprite(map->map_start[0], map->map_start[1] + 1, map);
		if (is_valid(map->map_start[0] - 1, map->map_start[1], map))
			add_sprite(map->map_start[0] - 1, map->map_start[1], map);
		if (is_valid(map->map_start[0] + 1, map->map_start[1], map))
			add_sprite(map->map_start[0] + 1, map->map_start[1], map);
	}
}
