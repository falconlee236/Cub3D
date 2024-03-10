/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:17:34 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/10 15:52:13 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
