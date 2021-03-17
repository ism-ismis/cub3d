/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:05:41 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 12:05:42 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_nbr(unsigned int nb2, int fd)
{
	if (nb2 / 10 == 0)
		ft_putchar_fd(nb2 + '0', fd);
	else
	{
		print_nbr(nb2 / 10, fd);
		ft_putchar_fd(nb2 % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int n2;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n2 = -1 * n;
	}
	else
		n2 = n;
	print_nbr(n2, fd);
}
