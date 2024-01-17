/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:09:36 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/17 15:20:53 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//LINK - vec_nev : 벡터의 생성
t_vec	vec_new(double x, double y)
{
	t_vec	res;

	res.x = x;
	res.y = y;
	return (res);
}

//LINK - vec_add : 벡터의 덧셈
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

//LINK - vec_sub : 벡터의 뺄셈
t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

//LINK - vec_mul : 벡터의 곱셈
t_vec	vec_mul(t_vec a, double c)
{
	t_vec	res;

	res.x = c * a.x;
	res.y = c * a.y;
	return (res);
}
