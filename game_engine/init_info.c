/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 00:03:38 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 12:38:49 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_text		*init_texture(int size)
{
	int		i;
	t_text	*t;

	if (!(t = (t_text *)malloc(sizeof(t_text) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		t[i].t_width = 0;
		t[i].t_height = 0;
		t[i].text = NULL;
		i++;
	}
	return (t);
}

int			**init_buf(t_info *info)
{
	int	**buf;
	int	i;
	int j;

	if (!(buf = (int **)malloc(sizeof(int *) * info->height)))
		return (NULL);
	i = 0;
	while (i < info->height)
	{
		if (!(buf[i] = (int *)malloc(sizeof(int) * info->width)))
			free_buf(buf, i);
		i++;
	}
	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width)
		{
			buf[i][j] = 0;
			j++;
		}
		i++;
	}
	return (buf);
}

t_key		*init_key(t_info *info)
{
	t_key *key;

	if (!(key = (t_key *)malloc(sizeof(t_key))))
		return (NULL);
	info->key = key;
	key->forward = 0;
	key->backward = 0;
	key->right = 0;
	key->left = 0;
	key->turn_right = 0;
	key->turn_left = 0;
	return (key);
}

t_sprite	*init_sp_list(t_cub *map, t_info *info)
{
	t_sprite	*sp_list;
	int			i;
	int			x;
	int			y;

	if (!(sp_list = (t_sprite *)malloc(sizeof(t_sprite) * map->sprite_num)))
		return (NULL);
	i = 0;
	y = 0;
	while (y < map->map_row)
	{
		x = 0;
		while (info->map_array[y][x] && i < map->sprite_num)
		{
			if (info->map_array[y][x] == '2')
			{
				sp_list[i].x = x;
				sp_list[i].y = y;
				i++;
			}
			x++;
		}
		y++;
	}
	return (sp_list);
}

int			init_info(t_cub *map, t_info *info)
{
	info->img.img = NULL;
	info->win = NULL;
	info->mov_speed = 0.05;
	info->rot_speed = 0.05;
	info->key = 0;
	info->map = map;
	info->z_buffer = (double *)malloc(sizeof(double) * info->width);
	info->buf = init_buf(info);
	if (!(info->texture = init_texture(5)))
		return (-1);
	info->pos_x = (double)map->player_x + 0.5;
	info->pos_y = (double)map->player_y + 0.5;
	info->f_color = map->f_color;
	info->c_color = map->c_color;
	info->map_array = map->map_array;
	copy_map_info(map, info);
	info->key = init_key(info);
	info->sp_list = init_sp_list(map, info);
	info->error = 0;
	return (0);
}
