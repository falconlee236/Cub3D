/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:13:23 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/15 22:05:53 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include "../cub3d.h"
# include "../libft/libft.h"

typedef struct s_map	t_map;

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char **s1, char *s2);
int		free_map(t_map *map);
int		init_map(int argc, char **argv, t_map *map);
void	*ft_free(char **target);

#endif
