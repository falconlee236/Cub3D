/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:10:32 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/14 11:14:16 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_hex(unsigned int n)
{
	char	arr[30];
	int		cnt;
	int		i;

	cnt = 0;
	if (n == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		return (1);
	}
	while (n)
	{
		arr[cnt++] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	i = cnt;
	while (i > 0)
	{
		if (write(1, &arr[--i], 1) == -1)
			return (-1);
	}
	return (cnt);
}

int	format_x(unsigned int x)
{
	return (ft_putnbr_hex(x));
}
