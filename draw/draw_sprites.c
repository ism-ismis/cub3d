/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:49:08 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/23 14:11:16 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		free_sprites(t_sprites *head)
{
	t_sprites *p;

	if (!head)
		return ;
	while (head)
	{
		p = head;
		head = head->next;
		safe_free(p);
	}
}

void		find_sprite_order(t_sprites **new, t_sprites **now)
{
	while (*now)
	{
		if (!(*now)->next)
		{
			(*now)->next = *new;
			break ;
		}
		else if ((*new)->distance <= (*now)->distance &&
		(*new)->distance > (*now)->next->distance)
		{
			(*new)->next = (*now)->next;
			(*now)->next = *new;
			break ;
		}
		*now = (*now)->next;
	}
}

void		sort_sprites(t_sprites **head, t_sprites **new,
			t_sprites **now, int *i)
{
	(*new)->next = NULL;
	if (!(*head))
		*head = *new;
	else if ((*new)->distance > (*head)->distance)
	{
		(*new)->next = *head;
		*head = *new;
	}
	else
	{
		*now = *head;
		find_sprite_order(new, now);
	}
	(*i)++;
}

t_sprites	*add_sort_sprites(t_info *info)
{
	int			i;
	t_sprites	*head;
	t_sprites	*now;
	t_sprites	*new;

	i = 0;
	head = NULL;
	while (i < info->map->sprite_num)
	{
		if (!(new = (t_sprites *)malloc(sizeof(t_sprites))))
		{
			free_sprites(head);
			info->error = 1;
			return (NULL);
		}
		new->x = (double)(info->sp_list[i].x) + 0.5;
		new->y = (double)(info->sp_list[i].y) + 0.5;
		new->distance = ((info->pos_x - new->x) * (info->pos_x - new->x)) +
		((info->pos_y - new->y) * (info->pos_y - new->y));
		sort_sprites(&head, &new, &now, &i);
	}
	now = head;
	while (now != NULL)
		now = now->next;
	return (head);
}

int			cast_sprites(t_info *info)
{
	t_sprites	*head;

	head = add_sort_sprites(info);
	if (draw_sprites(info, &head) == -1)
	{
		free_sprites(head);
		return (-1);
	}
	free_sprites(head);
	return (0);
}
