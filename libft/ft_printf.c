/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:26:10 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/19 19:27:06 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_type(char type, va_list ap)
{
	int	ans;

	if (type == 'c')
		ans = format_c(va_arg(ap, int));
	else if (type == 's')
		ans = format_s(va_arg(ap, char *));
	else if (type == 'p')
		ans = format_p(va_arg(ap, void *));
	else if (type == 'd')
		ans = format_d(va_arg(ap, int));
	else if (type == 'i')
		ans = format_d(va_arg(ap, int));
	else if (type == 'u')
		ans = format_u(va_arg(ap, unsigned int));
	else if (type == 'x')
		ans = format_x(va_arg(ap, unsigned int));
	else if (type == 'X')
		ans = format_x_upper(va_arg(ap, unsigned int));
	else if (type == '%')
		ans = format_c('%');
	else
		ans = -1;
	return (ans);
}

static int	check_format(char c, va_list ap, int *cnt)
{
	int	ans;

	ans = format_type(c, ap);
	if (ans == -1)
	{
		va_end(ap);
		return (0);
	}
	(*cnt) += ans;
	return (1);
}

static int	check_write(char c, va_list ap, int *cnt)
{
	(*cnt)++;
	if (write(1, &c, 1) == -1)
	{
		va_end(ap);
		return (0);
	}
	return (1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		cnt;
	int		i;

	va_start(ap, str);
	cnt = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			if (!check_format(str[++i], ap, &cnt))
				return (-1);
		}
		else
		{
			if (!check_write(str[i], ap, &cnt))
				return (-1);
		}
	}
	va_end(ap);
	return (cnt);
}
