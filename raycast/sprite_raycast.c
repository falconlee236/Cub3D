/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:22:18 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/17 17:52:05 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define SPRITE_NUM 19

struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

struct Sprite	sprite[SPRITE_NUM] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

void	sort_order(t_pair *orders)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < SPRITE_NUM)
	{
		j = 0;
		while (j < SPRITE_NUM - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *sprite_order, double *sprite_dist)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair *)malloc(sizeof(t_pair) * SPRITE_NUM);
	if (!sprites)
		exit(0);
	i = 0;
	while (i < SPRITE_NUM)
	{
		sprites[i].first = sprite_dist[i];
		sprites[i].second = sprite_order[i];
		i++;
	}
	sort_order(sprites);
	i = 0;
	while (i < SPRITE_NUM)
	{
		sprite_dist[i] = sprites[SPRITE_NUM - i - 1].first;
		sprite_order[i] = sprites[SPRITE_NUM - i - 1].second;
		i++;
	}
	free(sprites);
}

int	cal_sprite_raycast(t_screen *s, int *sprite_order, double *sprite_dist)
{
	int	i;

	if (!sprite_order || !sprite_dist)
		return (1);
	i = 0;
	while (i < SPRITE_NUM)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((s->pos.x - sprite[i].x) * (s->pos.x - sprite[i].x)
				+ (s->pos.y - sprite[i].y) * (s->pos.y - sprite[i].y));
		i++;
	}
	sort_sprites(sprite_order, sprite_dist);
	return (0);
}

void	sprite_raycast(t_screen *s)
{
	int		*sprite_order;
	double	*sprite_dist;

	sprite_order = (int *)malloc(sizeof(int) * SPRITE_NUM);
	sprite_dist = (double *)malloc(sizeof(double) * SPRITE_NUM);
	if (cal_sprite_raycast(s, sprite_order, sprite_dist))
		exit(0);
	free(sprite_order);
	free(sprite_dist);
}
