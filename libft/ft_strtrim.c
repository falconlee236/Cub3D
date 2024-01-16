/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:04 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/22 16:20:54 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	len_front(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		if (check_set(set, s1[i]))
			i++;
		else
			break ;
	}
	return (i);
}

size_t	len_behind(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	if (len == 0)
		return (0);
	i = len - 1;
	while (i >= 0)
	{
		if (check_set(set, s1[i]))
		{
			if (i == 0)
				return (0);
			i--;
		}
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	idx;
	char	*res;

	i = len_front(s1, set);
	j = len_behind(s1, set);
	idx = 0;
	if (i >= j)
		res = (char *)malloc(1);
	else
		res = (char *)malloc(j - i + 2);
	if (!res)
		return (NULL);
	if (i != 0 || j != 0)
	{
		while (i <= j)
		{
			res[idx] = s1[i];
			i++;
			idx++;
		}
	}
	res[idx] = '\0';
	return (res);
}
