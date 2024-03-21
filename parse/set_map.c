/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:41:21 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/21 21:04:06 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_map(char *filename, t_map *map)
{
	char	*tmp_line;
	int		fd;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Failed to Open File.");
	i = 1;
	while (i < map->max_height)
	{
		tmp_line = get_next_line(fd);
		if (!tmp_line)
			break ;
		free(tmp_line);
		i++;
	}
	close(fd);
}

void	alloc_map(t_map *map)
{
	size_t	i;

	map->map = (int **)malloc(map->max_height * sizeof(int *));
	if (!(map->map))
		exit_error("Allocation Error.");
	i = 0;
	while (i < map->max_height)
	{
		(map->map)[i] = (int *)malloc(map->max_height * sizeof(int));
		if (!(map->map)[i])
			exit_error("Allocation Error.");
		i++;
	}
}
