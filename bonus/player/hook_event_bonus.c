/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_event_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:17:34 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/24 16:05:16 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	key_press(int key, t_screen *s)
{
	if (key == KEY_W)
		s->move.key_w = 1;
	if (key == KEY_S)
		s->move.key_s = 1;
	if (key == KEY_A)
		s->move.key_a = 1;
	if (key == KEY_D)
		s->move.key_d = 1;
	if (key == KEY_AR_R)
		s->move.key_arr_r = 1;
	if (key == KEY_AR_L)
		s->move.key_arr_l = 1;
	if (key == KEY_1)
	{
		s->mouse_toggle = 1;
		mlx_mouse_hide();
	}
	if (key == KEY_2)
	{
		s->mouse_toggle = 0;
		mlx_mouse_show();
	}
	if (key == KEY_ESC || key == 65307)
		destory_hook_event(s);
	return (0);
}

int	key_release(int key, t_screen *s)
{
	if (key == KEY_W)
		s->move.key_w = 0;
	if (key == KEY_S)
		s->move.key_s = 0;
	if (key == KEY_A)
		s->move.key_a = 0;
	if (key == KEY_D)
		s->move.key_d = 0;
	if (key == KEY_AR_R)
		s->move.key_arr_r = 0;
	if (key == KEY_AR_L)
		s->move.key_arr_l = 0;
	return (0);
}

int	key_hook_event(t_screen *s)
{
	if (s->move.key_w || s->move.key_s)
		move_front_back(s);
	if (s->move.key_a || s->move.key_d)
		move_left_right(s);
	if (s->move.key_arr_l || s->move.key_arr_r)
		rot_left_right(s);
	return (0);
}

int	destory_hook_event(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}

int	mouse_hook_event(int x, int y, t_screen *s)
{
	y = 2;
	if (s->mouse_toggle)
	{
		mlx_mouse_move(s->win, SCREEN_W / y, SCREEN_H / y);
		s->dir = vec_rot(s->dir, s->rotspeed * (SCREEN_W / 2 - x) * 0.05);
		s->plane = vec_rot(s->plane, s->rotspeed * (SCREEN_W / 2 - x) * 0.05);
	}
	return (0);
}
