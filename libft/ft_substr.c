/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:21:19 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/14 14:36:32 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!s[i] || len < 1 || ft_strlen(s) < start)
		len = 0;
	if (!(p = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len >= i + 1 && s[start])
	{
		p[i++] = s[start++];
	}
	p[i] = '\0';
	return (p);
}
