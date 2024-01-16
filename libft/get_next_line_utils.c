/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:06:45 by sangylee          #+#    #+#             */
/*   Updated: 2023/07/14 16:59:28 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	size_t	size;
	char	*res;

	if (!s || *s == 0)
		return (NULL);
	s_len = ft_strlen_gnl(s);
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

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*res;

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	i = -1;
	res = (char *)malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	while (++i < s1_len)
		res[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		res[i + s1_len] = s2[i];
	res[s1_len + s2_len] = '\0';
	return (res);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen_gnl(s);
	while (i < len)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup_gnl(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen_gnl(s1);
	if (!s1 || *s1 == 0)
		return (NULL);
	res = (char *)malloc(len + 1);
	i = 0;
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
