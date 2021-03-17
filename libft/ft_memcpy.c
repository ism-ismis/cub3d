/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:00:54 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 12:01:01 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *pd;
	unsigned char *ps;

	if (!dst && !src)
		return (NULL);
	pd = (unsigned char*)dst;
	ps = (unsigned char*)src;
	while (n > 0)
	{
		*pd++ = *ps++;
		n--;
	}
	return (dst);
}
