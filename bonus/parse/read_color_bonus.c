/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:30:36 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 16:05:01 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

static int	only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	rgb_to_int(char *str)
{
	int	num;

	num = 0;
	while (*str)
	{
		num = num * 10 + (*str - '0');
		if (!(0 <= num && num <= 255))
			exit_error("Invalid File Content.");
		str++;
	}
	return (num);
}

int	get_color(char *rgb_str)
{
	int		i;
	int		cnt;
	int		rgb_int;
	int		rgb[3];
	char	**rgb_arr;

	cnt = 0;
	i = 0;
	while (rgb_str[i])
		if (rgb_str[i++] == ',')
			cnt++;
	rgb_arr = ft_split(rgb_str, ',');
	if (cnt != 2 || !rgb_arr[0] || !rgb_arr[1] || !rgb_arr[2]
		|| !only_digit(rgb_arr[0])
		|| !only_digit(rgb_arr[1])
		|| !only_digit(rgb_arr[2]))
		exit_error("Invalid File Content.");
	rgb[0] = rgb_to_int(rgb_arr[0]);
	rgb[1] = rgb_to_int(rgb_arr[1]);
	rgb[2] = rgb_to_int(rgb_arr[2]);
	rgb_int = rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2];
	free_str_arr(rgb_arr, NULL);
	return (rgb_int);
}
