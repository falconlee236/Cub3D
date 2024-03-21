/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:25:58 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/21 17:36:21 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	check_valid_data(int fd, int data_cnt, t_map *map)
{
	if (data_cnt != 6)
		exit(-1);
	if (close(fd) < 0)
		exit(-1);
	fd = open(map->east_texture, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		exit(-1);
	fd = open(map->west_texture, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		exit(-1);
	fd = open(map->north_texture, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		exit(-1);
	fd = open(map->south_texture, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		exit(-1);
	if (map->ceiling_color < 0
		|| map->floor_color < 0)
		exit(-1);
}

static void	set_data(char **arr_line, t_map *map)
{
	if (ft_strcmp(arr_line[0], "EA") == 0 && !(map->east_texture))
		map->east_texture = ft_strdup(arr_line[1]);
	else if (ft_strcmp(arr_line[0], "WE") == 0 && !(map->west_texture))
		map->west_texture = ft_strdup(arr_line[1]);
	else if (ft_strcmp(arr_line[0], "NO") == 0 && !(map->north_texture))
		map->north_texture = ft_strdup(arr_line[1]);
	else if (ft_strcmp(arr_line[0], "SO") == 0 && !(map->south_texture))
		map->south_texture = ft_strdup(arr_line[1]);
	else if (ft_strcmp(arr_line[0], "C") == 0 && map->ceiling_color < 0)
		map->ceiling_color = get_color(arr_line[1]);
	else if (ft_strcmp(arr_line[0], "F") == 0 && map->floor_color < 0)
		map->floor_color = get_color(arr_line[1]);
	else
		exit(-1);
}

void	read_file_data(char *filename, t_map *map)
{
	char	**arr_line;
	char	*tmp_line;
	int		data_cnt;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(0);
	data_cnt = 0;
	while (1)
	{
		tmp_line = get_next_line(fd);
		if (!tmp_line)
			break ;
		if (ft_strcmp(tmp_line, "\n") == 0)
		{
			free(tmp_line);
			continue ;
		}
		arr_line = ft_split(tmp_line, ' ');
		set_data(arr_line, map);
		free_str_arr(arr_line, tmp_line);
	}
	check_valid_data(fd, data_cnt, map);
}
