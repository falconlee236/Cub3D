/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:36:46 by sangylee          #+#    #+#             */
/*   Updated: 2023/04/02 15:45:22 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*make_next_line(char **backup, char *find)
{
	char	*tmp;
	char	*res;

	if (find)
	{
		res = ft_substr(*backup, 0, find - (*backup) + 1);
		if (!res)
			return (NULL);
		tmp = ft_strdup(find + 1);
		if (!tmp && *(find + 1) != '\0')
		{
			free(res);
			return (NULL);
		}
	}
	else
	{
		tmp = NULL;
		res = ft_strdup(*backup);
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
		tmp = ft_strjoin(*backup, buff);
		free(*backup);
		*backup = tmp;
		*find = ft_strchr(*backup, '\n');
		if (*find || !byte)
			break ;
	}
	free(buff);
	return (1);
}

static void	t_fileclear(t_file **lst, int fd)
{
	t_file	*cur;
	t_file	*prev;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	if (cur->fd == fd)
	{
		free(cur->backup);
		*lst = cur->next;
		free(cur);
		return ;
	}
	while (cur)
	{
		if (cur->fd == fd)
		{
			free(cur->backup);
			prev->next = cur->next;
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static t_file	*find_file_info(t_file **data, int fd)
{
	t_file	*node;
	t_file	*start;

	start = *data;
	while (start)
	{
		if (start->fd == fd)
			return (start);
		if (start->next == NULL)
			break ;
		start = start->next;
	}
	node = (t_file *)malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	node->backup = NULL;
	if (*data)
		start->next = node;
	else
		*data = node;
	return (node);
}

char	*get_next_line(int fd)
{
	char			*find;
	static t_file	*files = 0;
	char			*ret;
	t_file			*node;

	node = find_file_info(&files, fd);
	if (read(fd, 0, 0) == -1 || !node
		|| !find_next_line(&(node->backup), &find, fd))
	{
		t_fileclear(&files, fd);
		return (NULL);
	}
	ret = make_next_line(&(node->backup), find);
	if (!ret)
		t_fileclear(&files, fd);
	return (ret);
}
