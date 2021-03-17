/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:58:23 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 22:22:31 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*pd;
	unsigned char	*ps;

	pd = (unsigned char*)dst;
	ps = (unsigned char*)src;
	while (n > 0)
	{
		if (*ps != (unsigned char)c)
			*pd++ = *ps++;
		else
		{
			*pd++ = *ps++;
			return (pd);
		}
		n--;
	}
	return (NULL);
}
