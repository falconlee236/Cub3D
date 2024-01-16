/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:48:14 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/17 13:57:29 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		*((unsigned char *)mem + i) = 0;
		i++;
	}
	return (mem);
}
