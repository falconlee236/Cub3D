/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 06:00:32 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 16:04:54 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

void	*ft_free(char **target)
{
	if (!(*target))
		return (NULL);
	free(*target);
	*target = NULL;
	return (*target);
}

char	*ft_strjoin_gnl(char **s1, char *s2)
{
	char	*res;
	ssize_t	i;
	ssize_t	size1;
	ssize_t	size2;

	if (!(*s1) || !s2)
		return (ft_free(s1));
	size1 = ft_strlen(*s1);
	size2 = ft_strlen(s2);
	res = (char *)malloc(size1 + size2 + 1);
	if (!res)
		return (ft_free(s1));
	i = -1;
	while ((*s1)[++i])
		res[i] = (*s1)[i];
	i = -1;
	while (s2[++i])
		res[i + size1] = s2[i];
	res[i + size1] = '\0';
	ft_free(s1);
	return (res);
}
