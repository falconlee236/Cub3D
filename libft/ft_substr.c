/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:37 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/22 16:11:32 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	size_t	size;
	char	*res;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		size = 0;
	else if (len >= s_len - start)
		size = s_len - start;
	else
		size = len;
	res = (char *)malloc(size + 1);
	i = 0;
	if (!res)
		return (NULL);
	while (start < s_len && i < len)
	{
		res[i] = s[start++];
		i++;
	}
	res[i] = '\0';
	return (res);
}
