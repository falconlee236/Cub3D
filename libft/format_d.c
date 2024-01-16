/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:50:22 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/14 11:10:34 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr(int n)
{
	char	arr[15];
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
		arr[cnt++] = (n % 10) + '0';
		n /= 10;
	}
	i = cnt;
	while (i > 0)
	{
		if (write(1, &arr[--i], 1) == -1)
			return (-1);
	}
	return (cnt);
}

int	format_d(int d)
{
	if (d == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	if (d < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		return (ft_putnbr(-d) + 1);
	}
	else
		return (ft_putnbr(d));
}
