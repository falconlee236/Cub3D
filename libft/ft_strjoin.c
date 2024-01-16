/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:29:30 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/22 16:18:33 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	set_len(size_t *s1_len, size_t *s2_len, char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	*s1_len = ft_strlen(s1);
	*s2_len = ft_strlen(s2);
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*res;

	if (!set_len(&s1_len, &s2_len, s1, s2))
		return (NULL);
	i = 0;
	res = (char *)malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	while (i < s1_len)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		res[i + s1_len] = s2[i];
		i++;
	}
	res[s1_len + s2_len] = '\0';
	return (res);
}
