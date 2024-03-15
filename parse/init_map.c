/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:10:42 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/15 21:53:06 by yonyoo           ###   ########seoul.kr  */
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

int	init_map(int argc, char **argv, t_map *map)
{
	(void)map;
	if (argc != 2 || !argv || !(argv[1]))
		return (0);
	if (!check_filename(argv[1]))
		return (0);
	return (1);
}
