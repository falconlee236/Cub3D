/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:41:21 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 04:22:13 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
			{
				close(fd);
				exit_error("Invalid Map Content.");
			}
			map->init_direction = line[idx];
			map->map_start[0] = height;
			map->map_start[1] = idx;
		}
		else
		{
			close(fd);
			exit_error("Invalid Map Content.");
		}
		idx++;
	}
	if (line)
		free(line);
}

static int	is_data(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "EA", 2) == 0
		|| ft_strncmp(str, "WE", 2) == 0
		|| ft_strncmp(str, "NO", 2) == 0
		|| ft_strncmp(str, "SO", 2) == 0
		|| ft_strncmp(str, "F ", 2) == 0
		|| ft_strncmp(str, "C ", 2) == 0
		|| ft_strlen(str) == 0)
		return (1);
	return (0);
}

static char	*skip_lines(int fd, int *idx)
{
	char	*tmp_line;

	while (1)
	{
		tmp_line = get_next_line_nonl(fd);
		if (!tmp_line)
		{
			close(fd);
			exit_error("Failed to Read File.");
		}
		if (!is_data(tmp_line))
			return (tmp_line);
		(*idx)++;
		free(tmp_line);
	}
}

void	set_map(char *filename, t_map *map)
{
	char	*tmp_line;
	int		fd;
	size_t	idx;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Failed to Open File.");
	idx = 0;
	tmp_line = skip_lines(fd, (int *)&idx);
	if ((int)idx != map->map_start_line)
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

void	alloc_map(t_map *map)
{
	size_t	i;

	map->map = (int **)ft_calloc(map->max_height, sizeof(int *));
	if (!(map->map))
		exit_error("Allocation Error.");
	i = 0;
	while (i < map->max_height)
	{
		(map->map)[i] = (int *)ft_calloc(map->max_width, sizeof(int));
		if (!(map->map)[i])
			exit_error("Allocation Error.");
		i++;
	}
}
