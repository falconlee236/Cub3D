/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:10:42 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/15 21:24:03 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_filename(char *str)
{
	(void)str;
	return (1);
}

int	init_map(int argc, char **argv, t_map *map)
{
	if (argc != 2)
		return (0);
	if (!check_filename(argv[1]))
		return (0);
	return (1);
}
