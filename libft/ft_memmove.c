/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:21:06 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/21 19:37:03 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	tmp;

	if (!src && !dst)
		return (dst);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			tmp = len - i - 1;
			*((unsigned char *)(dst + tmp)) = *((unsigned char *)(src + tmp));
			i++;
		}
	}
	return (dst);
}
