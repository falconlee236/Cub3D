/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:10:42 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/21 19:21:44 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	check_filename(char *str)
{
	size_t	filename_len;

	filename_len = ft_strlen(str);
	if (filename_len > 4 && ft_strncmp(str + filename_len - 4, ".cub", 4) != 0)
		exit_error("Not a Valid File.");
}

static void	init_variable(t_map *map)
{
	map->map = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->east_texture = NULL;
	map->west_texture = NULL;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->init_direction = -1;
	map->max_height = -1;
	map->max_width = -1;
}

void	init_map(int argc, char **argv, t_map *map)
{
	init_variable(map);
	if (argc != 2 || !argv || !(argv[1]))
		exit_error("Invalid Argument.");
	check_filename(argv[1]);
	read_file_data(argv[1], map);
	alloc_map(map);
	set_map(argv[1], map);
}
