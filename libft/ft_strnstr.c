/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:19:52 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/14 14:05:39 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	const char	*p_ned;

	i = 0;
	p_ned = needle;
	while (*haystack && *p_ned && i < len)
	{
		if (*haystack == *p_ned)
		{
			haystack++;
			p_ned++;
			i++;
		}
		else
		{
			haystack -= p_ned - needle - 1;
			i -= p_ned - needle - 1;
			p_ned = needle;
		}
	}
	return (*p_ned ? NULL : (char *)(haystack - (p_ned - needle)));
}
