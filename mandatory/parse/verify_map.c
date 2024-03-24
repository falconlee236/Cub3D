/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:21:10 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 15:47:52 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_point(int newH, int newW, t_map *map)
{
	if (newH < 0 || newH >= (int)map->max_height
		|| newW < 0 || newW >= (int)map->max_width)
		exit_error("Invalid Map.");
	if (map->map[newH][newW] == 1
		|| map->map_is_visit[newH][newW])
		return (0);
	return (1);
}

static void	dfs_map(int curH, int curW, t_map *map)
{
	map->map_is_visit[curH][curW] = 1;
	if (curH < 0 || curH >= map->max_height
		|| curW < 0 || curW >= map->max_width
		|| map->map[curH][curW] == -1)
	{
		exit_error("Invalid Map.");
		return ;
	}
	if (check_point(curH, curW - 1, map))
		dfs_map(curH, curW - 1, map);
	if (check_point(curH, curW + 1, map))
		dfs_map(curH, curW + 1, map);
	if (check_point(curH - 1, curW, map))
		dfs_map(curH - 1, curW, map);
	if (check_point(curH + 1, curW, map))
		dfs_map(curH + 1, curW, map);
}

void	verify_map(t_map *map)
{
	int	i;
	int	j;

	if (map->map_start[0] < 0 || map->map_start[1] < 0)
		exit_error("Inavlid Map Content.");
	i = 0;
	while (i < map->max_height)
	{
		j = 0;
		while (j < map->max_width)
		{
			if (map->map[i][j] == 0 && !map->map_is_visit[i][j])
				dfs_map(i, j, map);
			j++;
		}
		i++;
	}
}
