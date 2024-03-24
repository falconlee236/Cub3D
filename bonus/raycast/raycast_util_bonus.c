/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:41:12 by isang-yun         #+#    #+#             */
/*   Updated: 2024/03/24 16:05:27 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	clear_buffer(t_screen *s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
			s->buf[i][j] = 0;
	}
}

t_pos	pos_new(int x, int y)
{
	t_pos	res;

	res.x = x;
	res.y = y;
	return (res);
}

void	switch_buffer(t_screen *s)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			s->img.addr[y * SCREEN_W + x] = s->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(s->mlx, s->win, s->img.ptr, 0, 0);
}
