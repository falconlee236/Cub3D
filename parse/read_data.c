/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:39:41 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/17 11:18:32 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	valid_data(char *str)
{
	// Check if Data Lines or Empty Lines
	// If Not, return 0
}

int	read_data(char *str, int *data_cnt, int *is_ok, t_map *map)
{
	if (!is_data(str))
		return (0);
	// Set DAta Value / data_cnt ++
	// Check if All Data Loaded
	return (1);
}
