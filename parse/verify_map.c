/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:21:10 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 04:25:08 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	verify_map(t_map *map)
{
	if (map->map_start[0] < 0 || map->map_start[1] < 0)
		exit_error("Inavlid Map Content.");
}
