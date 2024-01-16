/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_x_upper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:14:14 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/14 11:15:09 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_hex_upper(unsigned int n)
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
		arr[cnt++] = "0123456789ABCDEF"[n % 16];
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

int	format_x_upper(unsigned int x)
{
	return (ft_putnbr_hex_upper(x));
}
