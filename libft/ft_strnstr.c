/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:01:33 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/22 16:09:58 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (len == 0 && !haystack)
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	if (*haystack == 0)
		return (NULL);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j]
			&& i + j < len && needle[j] && haystack[i + j])
			j++;
		if (needle_len == j)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
