/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:30:33 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 22:40:58 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	skip_space(char **str)
{
	while (**str && (**str == '\t' || **str == '\v' || **str == ' '))
		(*str)++;
}

int		get_kill_empty(int fd, char **line, char **ptr)
{
	if (get_next_line(fd, line) == -1)
		return (-1);
	*ptr = *line;
	while (!**ptr || (**ptr == '\t' || **ptr == '\v' || **ptr == ' '))
	{
		while (**ptr == '\t' || **ptr == '\v' || **ptr == ' ')
			(*ptr)++;
		if (**ptr == '\0')
		{
			safe_free(*line);
			get_next_line(fd, line);
			*ptr = *line;
		}
	}
	return (0);
}

int		atoi_rev(char **fmt)
{
	long long	res;
	int			zero;

	res = 0;
	zero = 0;
	if (**fmt == '-')
		res = -1;
	if (**fmt == '0')
		zero = 1;
	while (**fmt >= '0' && **fmt <= '9')
	{
		if (res > 0)
			res *= 10;
		if (res >= 0)
			res += **fmt - '0';
		if (res > 2147483647)
			res = 2147483647;
		(*fmt)++;
	}
	if (zero && res != 0)
		res = -1;
	return (res);
}

void	map_lstclear(t_list **lst)
{
	t_list	*p;

	if (!lst)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		free(p);
	}
	*lst = NULL;
}

void	map_lstclear_content(t_list **lst)
{
	t_list	*p;

	if (!lst)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		free(p->content);
		free(p);
	}
	*lst = NULL;
}
