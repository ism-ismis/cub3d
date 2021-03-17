/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:21:03 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 23:19:12 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_find(char c, char const *set)
{
	if (set == NULL)
		return (0);
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		len;
	int		beg;
	int		end;
	int		i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	beg = 0;
	while (s1[beg] && set_find(s1[beg], set))
		beg++;
	end = 1;
	while (s1[len - end] && set_find(s1[len - end], set))
		end++;
	len -= (beg + end - 1);
	len = len < 0 ? 0 : len;
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
		res[i++] = s1[beg++];
	res[i] = '\0';
	return (res);
}
