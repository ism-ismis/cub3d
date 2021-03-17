/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:04:51 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 21:40:20 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	char	head;
	char	tail;
	char	mask1;
	char	mask2;

	if ((unsigned char)c <= 0x7F)
	{
		write(fd, &c, sizeof(char));
	}
	else
	{
		mask1 = 0b00111111;
		mask2 = 0b11000000;
		head = ((unsigned char)c & mask2) >> 6 | mask2;
		tail = ((unsigned char)c & mask1) | 0b10000000;
		write(fd, &head, 1);
		write(fd, &tail, 1);
	}
}
