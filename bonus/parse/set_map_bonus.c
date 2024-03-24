/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:41:21 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 16:05:05 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

static void	set_row(int fd, char *line, int height, t_map *map)
{
	size_t	idx;

	idx = 0;
	while (line && line[idx])
	{
		if (ft_isdigit(line[idx]) || line[idx] == ' ')
			map->map[height][idx] = line[idx] - '0';
		else if (line[idx] == 'N'
			|| line[idx] == 'S'
			|| line[idx] == 'E'
			|| line[idx] == 'W')
		{
			if (map->map_start[0] >= 0 && map->map_start[1] >= 0)
				close_fd_exit(fd);
			map->init_direction = line[idx];
			map->map_start[0] = height;
			map->map_start[1] = idx;
			map->map[map->map_start[0]][map->map_start[1]] = 0;
		}
		else
			close_fd_exit(fd);
		idx++;
	}
	if (line)
		free(line);
}

void	set_map(char *filename, t_map *map)
{
	char	*tmp_line;
	int		fd;
	int		idx;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Failed to Open File.");
	idx = 0;
	tmp_line = skip_lines(fd, (int *)&idx);
	if (idx != map->map_start_line)
		exit_error("Failed to Read File.");
	set_row(fd, tmp_line, 0, map);
	idx = 1;
	while (idx < map->max_height)
	{
		tmp_line = get_next_line_nonl(fd);
		if (!tmp_line)
			break ;
		set_row(fd, tmp_line, idx, map);
		idx++;
	}
	close(fd);
}

void	init_map_value(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->max_height)
	{
		j = 0;
		while (j < map->max_width)
		{
			map->map[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	alloc_map(t_map *map)
{
	int	i;

	map->map = (int **)malloc(map->max_height * sizeof(int *));
	map->map_is_visit = (int **)malloc(map->max_height * sizeof(int *));
	if (!(map->map) || !(map->map))
		exit_error("Allocation Error.");
	i = 0;
	while (i < map->max_height)
	{
		(map->map)[i] = (int *)malloc(map->max_width * sizeof(int));
		(map->map_is_visit)[i] = (int *)malloc(map->max_width * sizeof(int));
		if (!(map->map)[i] || !(map->map_is_visit)[i])
			exit_error("Allocation Error.");
		i++;
	}
}
