/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:31:14 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/18 11:32:47 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digit(long long num)
{
	int	cnt;

	cnt = 0;
	while (num)
	{
		num /= 10;
		cnt++;
	}
	return (cnt);
}

char	*make_number(char *str, long long num)
{
	int	cnt;
	int	i;

	cnt = count_digit(num);
	i = 0;
	if (!str)
		return (NULL);
	while (num)
	{
		str[cnt - i - 1] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	str[cnt] = '\0';
	return (str);
}

char	*zero_handler(void)
{
	char	*res;

	res = (char *)malloc(2);
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*res;

	if (n == 0)
		return (zero_handler());
	else if (n < 0)
	{
		num = -(long long)n;
		res = (char *)malloc(count_digit(num) + 2);
		if (!res)
			return (NULL);
		res[0] = '-';
		make_number(res + 1, num);
	}
	else
	{
		num = n;
		res = (char *)malloc(count_digit(num) + 1);
		if (!res)
			return (NULL);
		make_number(res, num);
	}
	return (res);
}
