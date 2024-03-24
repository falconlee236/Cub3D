/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/24 15:23:16 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_screen *s)
{
	static int	cnt;

	cnt++;
	s->sprite_texture = s->sub_texture[(cnt / 4) % 4];
	if (s->re_buf == 1)
		clear_buffer(s);
	horizontal_raycast(s);
	vertical_raycast(s);
	sprite_raycast(s);
	switch_buffer(s);
	render_minimap(s);
	key_hook_event(s);
	return (0);
}

//LINK - Main.c
int	main(int argc, char **argv)
{
	t_map		map;
	t_screen	s;

	init_map(argc, argv, &map);
	init_struct(&s, &map);
	mlx_loop_hook(s.mlx, &main_loop, &s);
	mlx_hook(s.win, ON_DESTROY, 0, &destory_hook_event, &s);
	mlx_hook(s.win, X_EVENT_KEY_PRESS, 0, &key_press, &s);
	mlx_hook(s.win, X_EVENT_KEY_RELEASE, 0, &key_release, &s);
	mlx_hook(s.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook_event, &s);
	mlx_loop(s.mlx);
	return (0);
}
