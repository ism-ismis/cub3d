/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:50:58 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/26 18:04:59 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		draw_stripe(t_info *info, t_spinfo *spinfo)
{
	int	y;
	int	d;
	int	color;

	y = spinfo->drawstart_y;
	while (y < spinfo->drawend_y)
	{
		d = y * 256 - info->height * 128 + spinfo->sp_height * 128;
		spinfo->tex_y =
		((d * info->texture[4].t_height) / spinfo->sp_height) / 256;
		color = info->texture[4].text[(info->texture[4].t_width) *
		spinfo->tex_y + spinfo->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			info->buf[y][spinfo->stripe] = color;
		y++;
	}
}

t_spinfo	*sprite_init(t_info *info, t_sprites *tmp)
{
	t_spinfo	*spinfo;

	if (!(spinfo = (t_spinfo *)malloc(sizeof(t_spinfo))))
		return (NULL);
	spinfo->sprite_x = tmp->x - info->pos_x;
	spinfo->sprite_y = tmp->y - info->pos_y;
	spinfo->invdet =
	1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y);
	spinfo->transform_x = spinfo->invdet *
	(info->dir_y * spinfo->sprite_x - info->dir_x * spinfo->sprite_y);
	spinfo->transform_y = spinfo->invdet *
	(-info->plane_y * spinfo->sprite_x + info->plane_x * spinfo->sprite_y);
	return (spinfo);
}

void		sprite_get_drawpoint(t_info *info, t_spinfo *spinfo)
{
	spinfo->sp_screen_x =
	(int)((info->width / 2) * (1 + spinfo->transform_x / spinfo->transform_y));
	spinfo->sp_height = (int)fabs(info->height / spinfo->transform_y);
	spinfo->drawstart_y = -spinfo->sp_height / 2 + (info->height / 2);
	if (spinfo->drawstart_y < 0)
		spinfo->drawstart_y = 0;
	spinfo->drawend_y = spinfo->sp_height / 2 + (info->height / 2);
	if (spinfo->drawend_y >= info->height)
		spinfo->drawend_y = info->height - 1;
	spinfo->sp_width = (int)fabs(info->height / spinfo->transform_y);
	spinfo->drawstart_x = -spinfo->sp_width / 2 + spinfo->sp_screen_x;
	if (spinfo->drawstart_x < 0)
		spinfo->drawstart_x = 0;
	spinfo->drawend_x = spinfo->sp_width / 2 + spinfo->sp_screen_x;
	if (spinfo->drawend_x >= info->width)
		spinfo->drawend_x = info->width - 1;
}

int			draw_sprites(t_info *info, t_sprites **head)
{
	t_sprites	*tmp;
	t_spinfo	*spinfo;

	tmp = *head;
	while (tmp)
	{
		if (!(spinfo = sprite_init(info, tmp)))
			return (-1);
		sprite_get_drawpoint(info, spinfo);
		spinfo->stripe = spinfo->drawstart_x;
		while (spinfo->stripe < spinfo->drawend_x)
		{
			spinfo->tex_x = (int)((256 * (spinfo->stripe -
			(-spinfo->sp_width / 2 + spinfo->sp_screen_x)) *
			(info->texture[4].t_width) / spinfo->sp_width)) / 256;
			if (spinfo->transform_y > 0 && spinfo->stripe > 0
			&& spinfo->stripe < info->width
			&& spinfo->transform_y < info->z_buffer[spinfo->stripe])
				draw_stripe(info, spinfo);
			spinfo->stripe++;
		}
		safe_free(spinfo);
		tmp = tmp->next;
	}
	return (0);
}
