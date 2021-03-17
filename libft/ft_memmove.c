/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:01:13 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 12:01:35 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pd;
	unsigned char	*ps;

	if (!dst && !src)
		return (NULL);
	pd = (unsigned char*)dst;
	ps = (unsigned char*)src;
	if (pd > ps && pd < ps + len && len > 0)
	{
		pd += len - 1;
		ps += len - 1;
		while (len-- > 0)
		{
			*pd-- = *ps--;
		}
	}
	else
	{
		while (len-- > 0)
			*pd++ = *ps++;
	}
	return (dst);
}
