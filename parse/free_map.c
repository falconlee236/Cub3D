/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:19:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/15 21:22:53 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	free_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->max_height)
	{
		j = 0;
		while (j < map->max_width)
		{
			if ((map->map)[i][j])
				free((map->map)[i][j]);
			j++;
		}
		if ((map->map)[i])
			free((map->map)[i]);
		i++;
	}
	return (-1);
}
