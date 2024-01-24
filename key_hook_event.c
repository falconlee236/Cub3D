/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:17:34 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/24 12:29:46 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	g_worldmap[24][24];

static void	move_front_back(int key, t_screen *s)
{
	if (key == KEY_W)
	{
		if (!g_worldmap[
				(int)(s->pos.x + s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x += s->dir.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y + s->dir.y * s->movespeed)])
			s->pos.y += s->dir.y * s->movespeed;
	}
	else if (key == KEY_S)
	{
		if (!g_worldmap[
				(int)(s->pos.x - s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x -= s->dir.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y - s->dir.y * s->movespeed)])
			s->pos.y -= s->dir.y * s->movespeed;
	}
}

static void	rot_left_right(int key, t_screen *s)
{
	if (key == KEY_D)
	{
		s->dir = vec_rot(s->dir, -s->rotspeed);
		s->plane = vec_rot(s->plane, -s->rotspeed);
	}
	if (key == KEY_A)
	{
		s->dir = vec_rot(s->dir, s->rotspeed);
		s->plane = vec_rot(s->plane, s->rotspeed);
	}
}

int	key_hook_event(int key, t_screen *s)
{
	if (key == KEY_W)
		move_front_back(key, s);
	if (key == KEY_S)
		move_front_back(key, s);
	if (key == KEY_D)
		rot_left_right(key, s);
	if (key == KEY_A)
		rot_left_right(key, s);
	if (key == KEY_ESC)
		destory_hook_event(s);
	mlx_clear_window(s->mlx, s->win);
	main_loop(s);
	return (0);
}

int	destory_hook_event(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}
