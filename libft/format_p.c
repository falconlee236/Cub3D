/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:28:29 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/14 11:11:12 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_hex(unsigned long long n)
{
	char	arr[30];
	int		cnt;
	int		i;

	cnt = 0;
	if (n == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		return (3);
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
	return (cnt + 2);
}

int	format_p(void *ptr)
{
	if (write(1, "0x", 2) == -1)
		return (-1);
	return (ft_putnbr_hex((unsigned long long)ptr));
}
