/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:43:54 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/14 14:21:30 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	overflow_check(long long n, int sign)
{
	if (errno != ERANGE)
		return (n);
	if (sign == 1)
		return (-1);
	return (0);
}

int					ft_atoi(const char *str)
{
	int				sign;
	long long		res;

	sign = 1;
	res = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if (res)
			res *= 10;
		res += *str - '0';
		res = overflow_check(res, sign);
		str++;
	}
	return (res * sign);
}
