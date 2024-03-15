/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:41:21 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/15 22:45:06 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	alloc_map(t_map *map)
{
	size_t	i;

	map->map = (int **)malloc(map->max_height * sizeof(int *));
	if (!(map->map))
		return (0);
	i = 0;
	while (i < map->max_height)
	{
		(map->map)[i] = (int *)malloc(map->max_height * sizeof(int));
		if (!(map->map)[i])
			return (0);
		i++;
	}
	return (1);
}
