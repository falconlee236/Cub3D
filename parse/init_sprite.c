/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 05:09:22 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 05:18:32 by yonyoo           ###   ########seoul.kr  */
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

void	init_sprite(t_map *map)
{
	if (map->map_start[0] >= 1 && map->map_start[0] < map->max_height - 1
		&& map->map_start[1] >= 1 && map->map_start[1] < map->max_width - 1)
	{
		if (is_valid(map->map_start[0], map->map_start[1] - 1, map))
		{
			map->sprite_pos[0] = map->map_start[0];
			map->sprite_pos[1] = map->map_start[1] - 1;
		}
		else if (is_valid(map->map_start[0], map->map_start[1] + 1, map))
		{
			map->sprite_pos[0] = map->map_start[0];
			map->sprite_pos[1] = map->map_start[1] + 1;
		}
		else if (is_valid(map->map_start[0] - 1, map->map_start[1], map))
		{
			map->sprite_pos[0] = map->map_start[0] - 1;
			map->sprite_pos[1] = map->map_start[1];
		}
		else if (is_valid(map->map_start[0] + 1, map->map_start[1], map))
		{
			map->sprite_pos[0] = map->map_start[0] + 1;
			map->sprite_pos[1] = map->map_start[1];
		}
	}
}
