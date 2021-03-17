/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:56:45 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/13 22:14:48 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_el;

	if (!(new_el = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_el->content = content;
	new_el->next = NULL;
	return (new_el);
}
