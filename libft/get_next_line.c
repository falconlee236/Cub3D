/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:29:12 by sangylee          #+#    #+#             */
/*   Updated: 2023/07/14 16:58:35 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*make_next_line(char **backup, char *find)
{
	char	*tmp;
	char	*res;

	if (find)
	{
		res = ft_substr_gnl(*backup, 0, find - (*backup) + 1);
		if (!res)
			return (NULL);
		tmp = ft_strdup_gnl(find + 1);
		if (!tmp && *(find + 1) != '\0')
		{
			free(res);
			return (NULL);
		}
	}
	else
	{
		tmp = NULL;
		res = ft_strdup_gnl(*backup);
	}
	free(*backup);
	*backup = tmp;
	return (res);
}

static int	find_next_line(char **backup, char **find, int fd)
{
	int		byte;
	char	*buff;
	char	*tmp;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (1)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (!(*backup) && byte <= 0)
		{
			free(buff);
			return (0);
		}
		buff[byte] = '\0';
		tmp = ft_strjoin_gnl(*backup, buff);
		free(*backup);
		*backup = tmp;
		*find = ft_strchr_gnl(*backup, '\n');
		if (*find || !byte)
			break ;
	}
	free(buff);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*find;
	static char	*backup;
	char		*ret;

	if (read(fd, 0, 0) == -1 || !find_next_line(&backup, &find, fd))
	{
		free(backup);
		backup = 0;
		return (NULL);
	}
	ret = make_next_line(&backup, find);
	if (!ret)
	{
		free(backup);
		backup = 0;
	}
	return (ret);
}
