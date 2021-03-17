/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:29:14 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 23:08:50 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_info *info, int x, int y, int color)
{
	int *dst;

	dst = info->img.data +
	((y * info->img.size_l + x * (info->img.bpp / 8)) / sizeof(int));
	*dst = color;
}

void	draw(t_info *info)
{
	int y;
	int x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			my_mlx_pixel_put(info, x, y, info->buf[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	draw_floor_ceiling(t_info *info)
{
	int x;
	int y;
	int half;

	half = info->height / 2;
	y = 0;
	while (y + half < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->buf[y][x] = info->c_color;
			info->buf[y + half][x] = info->f_color;
			x++;
		}
		y++;
	}
}

void	wall_init(t_info *info, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)info->width - 1;
	ray->raydir_x = info->dir_x + info->plane_x * ray->camera_x;
	ray->raydir_y = info->dir_y + info->plane_y * ray->camera_x;
	ray->map_x = (int)info->pos_x;
	ray->map_y = (int)info->pos_y;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
}

void	wall_get_sidedist(t_info *info, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (info->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - info->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (info->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - info->pos_y) * ray->deltadist_y;
	}
}
