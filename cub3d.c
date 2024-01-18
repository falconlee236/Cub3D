/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/18 15:50:48 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leak_check(void)
{
	system("leaks cub3D");
}

int	destory_hook_event(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(1);
}

t_pixel	**init_pixel(int w, int h, t_img *img)
{
	t_pixel	**pixel;
	int		x;
	int		y;

	pixel = (t_pixel **)malloc(sizeof(t_pixel *) * w);
	x = -1;
	while (++x < w)
	{
		pixel[x] = (t_pixel *)malloc(sizeof(t_pixel) * h);
		y = -1;
		while (++y < h)
		{
			pixel[x][y].dist = INF;
			pixel[x][y].color = (unsigned int *)((char *)img->addr
					+ img->size_line * y + img->bits_per_pixel / 8 * x);
		}
	}
	return (pixel);
}

void	init_struct(t_screen *s)
{
	s->w = 1920;
	s->h = 1080;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, s->w, s->h, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx, s->w, s->h);
	s->img.addr = (unsigned int *)mlx_get_data_addr(s->img.ptr,
			&(s->img.bits_per_pixel), &(s->img.size_line), &(s->img.endian));
	s->dist = (s->w / 2) * (1 / tan(FOV / 2));
	s->pixel = init_pixel(s->w, s->h, &s->img);
	s->sin_unit = 0;
	s->cos_unit = 0;
}

//LINK - Main.c
int	main(void)
{
	t_screen	s;

	atexit(leak_check);
	init_struct(&s);
	mlx_hook(s.win, ON_DESTROY, 0, &destory_hook_event, &s);
	mlx_loop(s.mlx);
	return (0);
}
