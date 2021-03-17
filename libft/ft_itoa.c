/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:48:14 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 23:39:46 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_digit(unsigned int n2)
{
	int	digit_len;

	if (n2 == 0)
		return (1);
	digit_len = 0;
	while (n2 != 0)
	{
		n2 /= 10;
		digit_len++;
	}
	return (digit_len);
}

static char		*complete_num(unsigned int n2, int sign, int len, char *num)
{
	if (sign)
	{
		num[0] = '-';
		sign = 0;
	}
	if (n2 < 10)
	{
		num[len - 1] = n2 + '0';
	}
	else
	{
		complete_num(n2 / 10, sign, len - 1, num);
		num[len - 1] = (n2 % 10) + '0';
	}
	num[len] = '\0';
	return (num);
}

char			*ft_itoa(int n)
{
	char			*num;
	unsigned int	n2;
	int				sign;
	int				len;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n2 = n * -1;
	}
	else
		n2 = n;
	len = count_digit(n2);
	len = ((sign) ? len + 1 : len);
	if (!(num = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	return (complete_num(n2, sign, len, num));
}
