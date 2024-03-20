/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:51:10 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/10 15:54:01 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern int	g_worldmap[24][24];

void	move_front_back(t_screen *s)
{
	if (s->move.key_w && !s->move.key_s)
	{
		if (!g_worldmap[
				(int)(s->pos.x + s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x += s->dir.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y + s->dir.y * s->movespeed)])
			s->pos.y += s->dir.y * s->movespeed;
	}
	else if (s->move.key_s && !s->move.key_w)
	{
		if (!g_worldmap[
				(int)(s->pos.x - s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x -= s->dir.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y - s->dir.y * s->movespeed)])
			s->pos.y -= s->dir.y * s->movespeed;
	}
}

void	move_left_right(t_screen *s)
{
	if (s->move.key_d && !s->move.key_a)
	{
		if (!g_worldmap[
				(int)(s->pos.x + s->plane.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x += s->plane.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y + s->plane.y * s->movespeed)])
			s->pos.y += s->plane.y * s->movespeed;
	}
	else if (s->move.key_a && !s->move.key_d)
	{
		if (!g_worldmap[
				(int)(s->pos.x - s->plane.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x -= s->plane.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y - s->plane.y * s->movespeed)])
			s->pos.y -= s->plane.y * s->movespeed;
	}
}

void	rot_left_right(t_screen *s)
{
	if (s->move.key_arr_r && !s->move.key_arr_l)
	{
		s->dir = vec_rot(s->dir, -s->rotspeed);
		s->plane = vec_rot(s->plane, -s->rotspeed);
	}
	if (s->move.key_arr_l && !s->move.key_arr_r)
	{
		s->dir = vec_rot(s->dir, s->rotspeed);
		s->plane = vec_rot(s->plane, s->rotspeed);
	}
}
