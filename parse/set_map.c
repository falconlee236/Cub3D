/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:41:21 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/22 02:02:52 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

static void	skip_lines(int fd, int *idx)
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
		{
			free(tmp_line);
			break ;
		}
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
	skip_lines(fd, (int*)&idx);
	printf("AA %zu %d\n", idx, map->map_start_line);
	if((int)idx != map->map_start_line)
		exit_error("Failed to Read File.");
	while (idx < map->max_height)
	{
		tmp_line = get_next_line_nonl(fd);
		if (!tmp_line)
			break ;
		printf("AA #%s#\n", tmp_line);
		free(tmp_line);
		idx++;
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
