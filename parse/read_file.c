/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:25:58 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/17 10:01:51 by yonyoo           ###   ########seoul.kr  */
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

static int	set_map_size(int fd, t_map *map)
{
	char	*tmp_line;
	int		is_ok;

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
	if (map->max_height < 3 || !is_ok)
		return (0);
	return (1);
}

int	read_file(char *filename, t_map *map)
{
	char	*tmp_line;
	int		data_cnt;
	int		fd;
	int		is_ok;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	data_cnt = 0;
	is_ok = 1;
	while (is_ok > 0)
	{
		tmp_line = get_next_line(fd);
		if (!tmp_line && is_ok--)
			break ;
		if (!read_data(tmp_line, &data_cnt, &is_ok, map))
			break ;
	}
	if (is_ok)
		set_map_size(fd, map);
	close(fd);
	if (!is_ok)
		return (0);
	return (1);
}
