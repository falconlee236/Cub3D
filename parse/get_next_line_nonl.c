/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_nonl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:17:47 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/21 19:19:33 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*remove_nl(char *line)
{
	char	*str;
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] != '\n')
		return (line);
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		exit(EXIT_FAILURE);
	ft_strlcpy(str, line, len);
	free(line);
	return (str);
}

char	*get_next_line_nonl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	return (remove_nl(line));
}
