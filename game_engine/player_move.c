/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:15:34 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 17:37:32 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_info *info)
{
	if (info->map_array[(int)(info->pos_y + info->dir_y * info->mov_speed * 2)]
	[(int)info->pos_x] == '0')
		info->pos_y += info->dir_y * info->mov_speed;
	if (info->map_array[(int)info->pos_y]
	[(int)(info->pos_x + info->dir_x * info->mov_speed * 2)] == '0')
		info->pos_x += info->dir_x * info->mov_speed;
}

void	move_backward(t_info *info)
{
	if (info->map_array[(int)(info->pos_y - info->dir_y * info->mov_speed)]
	[(int)info->pos_x] == '0')
		info->pos_y -= info->dir_y * info->mov_speed;
	if (info->map_array[(int)info->pos_y]
	[(int)(info->pos_x - info->dir_x * info->mov_speed)] == '0')
		info->pos_x -= info->dir_x * info->mov_speed;
}

void	move_right(t_info *info)
{
	if (info->map_array[(int)(info->pos_y + info->plane_y * info->mov_speed)]
	[(int)info->pos_x] == '0')
		info->pos_y += info->plane_y * info->mov_speed;
	if (info->map_array[(int)info->pos_y]
	[(int)(info->pos_x + info->plane_x * info->mov_speed)] == '0')
		info->pos_x += info->plane_x * info->mov_speed;
}

void	move_left(t_info *info)
{
	if (info->map_array[(int)(info->pos_y - info->plane_y * info->mov_speed)]
	[(int)info->pos_x] == '0')
		info->pos_y -= info->plane_y * info->mov_speed;
	if (info->map_array[(int)info->pos_y]
	[(int)(info->pos_x - info->plane_x * info->mov_speed)] == '0')
		info->pos_x -= info->plane_x * info->mov_speed;
}

void	player_move(t_info *info)
{
	if (info->key->forward == 1)
		move_forward(info);
	if (info->key->backward == 1)
		move_backward(info);
	if (info->key->right == 1)
		move_right(info);
	if (info->key->left == 1)
		move_left(info);
	if (info->key->turn_right == 1)
		turn_right(info);
	if (info->key->turn_left == 1)
		turn_left(info);
}
