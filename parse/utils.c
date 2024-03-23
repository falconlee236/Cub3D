/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 04:56:48 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 04:58:22 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*skip_lines(int fd, int *idx)
{
	char	*tmp_line;

	while (1)
	{
		tmp_line = get_next_line_nonl(fd);
		if (!tmp_line)
		{
			close(fd);
			exit_error("Failed to Read File.");
		}
		if (!is_data(tmp_line))
			return (tmp_line);
		(*idx)++;
		free(tmp_line);
	}
}

int	is_data(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "EA", 2) == 0
		|| ft_strncmp(str, "WE", 2) == 0
		|| ft_strncmp(str, "NO", 2) == 0
		|| ft_strncmp(str, "SO", 2) == 0
		|| ft_strncmp(str, "F ", 2) == 0
		|| ft_strncmp(str, "C ", 2) == 0
		|| ft_strlen(str) == 0)
		return (1);
	return (0);
}

void	close_fd_exit(int fd)
{
	close(fd);
	exit_error("Invalid Map Content.");
}
