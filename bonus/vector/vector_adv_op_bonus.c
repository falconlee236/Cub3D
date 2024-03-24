/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_adv_op_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:19 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/24 16:05:40 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*LINK - get_dir_vec
두개 벡터가 주어지고, 이를 span으로 하는 좌표계에서 (x, y)좌표의 방향벡터 구하기
|a.x b.x|			|b.y -b.x|   1
|a.y b.y|  = X  	|-a.y a.x| * det = X의 역행렬
|x|
|y| = Y
Xv = Y를 만족하는 v벡터를 구하는 것이 목적. v = X의 역행렬 * Y
*/
t_vec	get_dir_vec(t_vec a, t_vec b, double x, double y)
{
	t_vec	res;
	double	det;

	det = a.x * b.y - b.x * a.y;
	res.x = ((b.y * x) + (-b.x * y)) / det;
	res.y = ((-a.y * x) + (a.x * y)) / det;
	return (res);
}

//LINK - vec_rot : 벡터의 반시계 회전, 맨 마지막 값은 호도법 사용
t_vec	vec_rot(t_vec a, int theta)
{
	t_vec	res;
	double	sin_theta;
	double	cos_theta;

	sin_theta = sin(theta * PI / 180);
	cos_theta = cos(theta * PI / 180);
	res.x = cos_theta * a.x - sin_theta * a.y;
	res.y = sin_theta * a.x + cos_theta * a.y;
	return (res);
}
