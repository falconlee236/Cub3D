/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:13:23 by yonyoo            #+#    #+#             */
/*   Updated: 2024/03/24 15:56:18 by yonyoo           ###   ########seoul.kr  */
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
# include "../../libft/libft.h"

typedef struct s_map	t_map;

char	*ft_strjoin_gnl(char **s1, char *s2);
char	*get_next_line(int fd);
char	*get_next_line_nonl(int fd);
char	*skip_lines(int fd, int *idx);
int		get_color(char *rgb_str);
int		is_data(char *str);
void	alloc_map(t_map *map);
void	close_fd_exit(int fd);
void	init_map(int argc, char **argv, t_map *map);
void	init_map_value(t_map *map);
void	init_sprite(t_map *map);
void	read_file_data(char *filename, t_map *map);
void	set_map(char *filename, t_map *map);
void	verify_map(t_map *map);
void	*ft_free(char **target);

#endif
