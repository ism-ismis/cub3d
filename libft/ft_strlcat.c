/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:17:36 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/14 13:55:17 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dest);
	if (size == 0 || size <= dst_len)
		return (size + src_len);
	dest += dst_len;
	size -= dst_len + 1;
	while (*src && size > 0)
	{
		*dest++ = *src++;
		size--;
	}
	*dest = '\0';
	return (dst_len + src_len);
}
