/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:23:36 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/17 15:42:28 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# define PI 3.14159265

//SECTION Vector struct
typedef struct s_vec{
	double	x;
	double	y;
}	t_vec;

#endif