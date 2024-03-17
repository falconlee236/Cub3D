/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:10:42 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/17 09:50:21 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_filename(char *str)
{
	size_t	filename_len;

	filename_len = ft_strlen(str);
	if (ft_strncmp(str + filename_len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	init_variable(t_map *map)
{
	map->map = NULL;
	map->floor_color = NULL;
	map->east_texture = NULL;
	map->west_texture = NULL;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->init_direction = 0;
	map->max_height = 0;
	map->max_width = 0;
}

int	init_map(int argc, char **argv, t_map *map)
{
	init_variable(map);
	if (argc != 2 || !argv || !(argv[1])
		|| !check_filename(argv[1])
		|| !read_file(argv[1], map)
		|| !alloc_map(map)
		|| !set_map(argv[1], map))
		return (0);
	return (1);
}
