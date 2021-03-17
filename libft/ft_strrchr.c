/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:20:15 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/14 14:02:14 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*p;
	unsigned char	uc;

	p = NULL;
	uc = c;
	while (1)
	{
		if (*s == uc)
			p = s;
		if (*s == '\0')
			break ;
		s++;
	}
	return ((char *)p);
}
