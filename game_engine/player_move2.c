/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:11:16 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 10:47:30 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		click_redcross(t_info *info)
{
	mlx_loop_end(info->mlx);
	return (0);
}

int		key_pressed(int key, t_info *info)
{
	if (key == K_ESC)
		mlx_loop_end(info->mlx);
	else if (key == K_W && info->key->forward == 0)
		info->key->forward = 1;
	else if (key == K_S && info->key->backward == 0)
		info->key->backward = 1;
	else if (key == K_D && info->key->right == 0)
		info->key->right = 1;
	else if (key == K_A && info->key->left == 0)
		info->key->left = 1;
	else if (key == K_AR_R && info->key->turn_right == 0)
		info->key->turn_right = 1;
	else if (key == K_AR_L && info->key->turn_left == 0)
		info->key->turn_left = 1;
	return (0);
}

int		key_released(int key, t_info *info)
{
	if (key == K_W)
		info->key->forward = 0;
	else if (key == K_S)
		info->key->backward = 0;
	else if (key == K_D && info->key->right == 1)
		info->key->right = 0;
	else if (key == K_A && info->key->left == 1)
		info->key->left = 0;
	else if (key == K_AR_R && info->key->turn_right == 1)
		info->key->turn_right = 0;
	else if (key == K_AR_L && info->key->turn_left == 1)
		info->key->turn_left = 0;
	return (0);
}

void	turn_right(t_info *info)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = info->dir_x;
	oldplane_x = info->plane_x;
	info->dir_x =
	info->dir_x * cos(info->rot_speed) - info->dir_y * sin(info->rot_speed);
	info->dir_y =
	olddir_x * sin(info->rot_speed) + info->dir_y * cos(info->rot_speed);
	info->plane_x =
	info->plane_x * cos(info->rot_speed) - info->plane_y * sin(info->rot_speed);
	info->plane_y =
	oldplane_x * sin(info->rot_speed) + info->plane_y * cos(info->rot_speed);
}

void	turn_left(t_info *info)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = info->dir_x;
	oldplane_x = info->plane_x;
	info->dir_x =
	info->dir_x * cos(-info->rot_speed) - info->dir_y * sin(-info->rot_speed);
	info->dir_y =
	olddir_x * sin(-info->rot_speed) + info->dir_y * cos(-info->rot_speed);
	info->plane_x = info->plane_x * cos(-info->rot_speed)
	- info->plane_y * sin(-info->rot_speed);
	info->plane_y =
	oldplane_x * sin(-info->rot_speed) + info->plane_y * cos(-info->rot_speed);
}
