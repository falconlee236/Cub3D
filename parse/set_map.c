/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:41:21 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/17 09:25:42 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	set_row(char *line, int line_idx, t_map *map)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(line) - 1;
	while (i < line_len)
	{
		(map->map)[line_idx][i] = line[i];
		i++;
	}
	while (i < map->max_width)
	{
		(map->map)[line_idx][i] = '0';
		i++;
	}
}

int	set_map(char *filename, t_map *map)
{
	char	*tmp_line;
	int		fd;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < map->max_height)
	{
		tmp_line = get_next_line(fd);
		if (!tmp_line)
			break ;
		set_row(tmp_line, i, map);
		free(tmp_line);
		i++;
	}
	close(fd);
	if (i != map->max_height)
		return (0);
	return (1);
}

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
