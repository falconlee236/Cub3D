/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:13:23 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/21 19:18:41 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../cub3d.h"
# include "../libft/libft.h"

typedef struct s_map	t_map;

char	*get_next_line(int fd);
char	*get_next_line_nonl(int fd);
char	*ft_strjoin_gnl(char **s1, char *s2);
int		alloc_map(t_map *map);
int		free_map(t_map *map);
int		get_color(char *rgb_str);
int		set_map(char *filename, t_map *map);
void	init_map(int argc, char **argv, t_map *map);
void	read_file_data(char *filename, t_map *map);
void	*ft_free(char **target);

#endif
