/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:26:43 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/19 18:04:51 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);

int		format_c(char c);
int		format_s(char *s);
int		format_p(void *ptr);
int		format_d(int d);
int		format_u(unsigned int u);
int		format_x(unsigned int x);
int		format_x_upper(unsigned int x);
#endif