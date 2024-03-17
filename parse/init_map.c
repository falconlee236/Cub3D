/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:10:42 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/17 09:24:39 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	set_map_width(char *line, t_map *map, int *is_ok)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len == 0)
		*is_ok = 0;
	if (map->max_width < len)
		map->max_width = len;
}

static int	set_map_size(char *filename, t_map *map)
{
	char	*tmp_line;
	int		fd;
	int		is_ok;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	is_ok = 1;
	while (is_ok > 0)
	{
		tmp_line = get_next_line(fd);
		if (!tmp_line)
			break ;
		set_map_width(tmp_line, map, &is_ok);
		free(tmp_line);
		(map->max_height)++;
	}
	close(fd);
	if (map->max_height < 3 || !is_ok)
		return (0);
	return (1);
}

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
		|| !set_map_size(argv[1], map)
		|| !alloc_map(map)
		|| !set_map(argv[1], map))
		return (0);
	return (1);
}
