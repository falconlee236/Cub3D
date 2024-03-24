/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:38:47 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/24 16:05:31 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	fill_squres(t_img *m_map, int x, int y, int color)
{
	int	i;
	int	j;
	int	idx;

	j = 0;
	idx = MINI_SCALE * SCREEN_W;
	while (j < (int)(MINI_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINI_SCALE * TILE_SIZE))
		{
			m_map->addr[idx * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

static void	cord_convert(t_screen *s, int x, int y, t_pos *conv_cord)
{
	if ((int)s->pos.x - MAP_NUM_ROWS / 2 + x < 0)
		conv_cord->x = 0;
	else if (
		(int)s->pos.x - MAP_NUM_ROWS / 2 + x >= (int)s->map->max_height)
		conv_cord->x = (int)s->map->max_height - 1;
	else
		conv_cord->x = (int)s->pos.x - MAP_NUM_ROWS / 2 + x;
	if ((int)s->pos.y - MAP_NUM_COLS / 2 + y < 0)
		conv_cord->y = 0;
	else if (
		(int)s->pos.y - MAP_NUM_COLS / 2 + y >= (int)s->map->max_width)
		conv_cord->y = (int)s->map->max_width - 1;
	else
		conv_cord->y = (int)s->pos.y - MAP_NUM_COLS / 2 + y;
}

static void	decide_color_and_drawing(
	t_screen *s, t_img m_map, t_pos conv_cord, t_pos cord)
{
	if ((s->map->map)[conv_cord.x][conv_cord.y])
		fill_squres(&m_map, (int)(MINI_SCALE * TILE_SIZE * cord.y),
			(int)(MINI_SCALE * TILE_SIZE * cord.x), 0x000000);
	else
		fill_squres(&m_map, (int)(MINI_SCALE * TILE_SIZE * cord.y),
			(int)(MINI_SCALE * TILE_SIZE * cord.x), 0xffffff);
	if (conv_cord.x == (int)s->pos.x && conv_cord.y == (int)s->pos.y)
		fill_squres(&m_map, (int)(MINI_SCALE * TILE_SIZE * cord.y),
			(int)(MINI_SCALE * TILE_SIZE * cord.x), 0xff0000);
}

void	render_minimap(t_screen *s)
{
	t_img		m_map;
	t_pos		conv_cord;
	t_pos		cord;

	m_map.ptr = mlx_new_image(
			s->mlx, (int)(MINI_SCALE * SCREEN_W), (int)(MINI_SCALE * SCREEN_H));
	m_map.addr = (unsigned int *)mlx_get_data_addr(m_map.ptr,
			&(m_map.bits_per_pixel), &(m_map.size_line), &(m_map.endian));
	cord.x = 0;
	while (cord.x < MAP_NUM_ROWS)
	{
		cord.y = 0;
		while (cord.y < MAP_NUM_COLS)
		{
			cord_convert(s, cord.x, cord.y, &conv_cord);
			decide_color_and_drawing(s, m_map, conv_cord, cord);
			cord.y++;
		}
		cord.x++;
	}
	mlx_put_image_to_window(s->mlx, s->win, m_map.ptr,
		(int)(SCREEN_W * (1.11 - MINI_SCALE)),
		(int)(SCREEN_H * (1.11 - MINI_SCALE)));
}
