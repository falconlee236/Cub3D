/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:05:30 by sangylee          #+#    #+#             */
/*   Updated: 2023/05/14 11:12:26 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_u(unsigned int n)
{
	char	arr[20];
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

int	format_u(unsigned int u)
{
	return (ft_putnbr_u(u));
}
