/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:19:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/17 09:16:23 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	free_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (map && map->map && i < map->max_height)
	{
		if ((map->map)[i])
			free((map->map)[i]);
		i++;
	}
	if (map && map->map)
		free(map->map);
	return (-1);
}
