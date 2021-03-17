/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:39:35 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 17:37:32 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_find_hit(t_info *info, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (info->map_array[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

int		get_tex_num(t_info *info, t_ray *ray)
{
	if (ray->side == 1)
	{
		if ((double)(ray->map_y) < info->pos_y)
			return (0);
		else
			return (1);
	}
	else
	{
		if ((double)(ray->map_x) > info->pos_x)
			return (2);
		else
			return (3);
	}
}

void	wall_get_perp_drawline(t_info *info, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwall_dist =
		(ray->map_x - info->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perpwall_dist =
		(ray->map_y - info->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
	ray->line_height = (int)(info->height / ray->perpwall_dist);
	ray->drawstart = -(ray->line_height) / 2 + info->height / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->line_height / 2 + info->height / 2;
	if (ray->drawend >= info->height)
		ray->drawend = info->height - 1;
	ray->tex_num = get_tex_num(info, ray);
	if (ray->side == 0)
		ray->wall_x = info->pos_y + ray->perpwall_dist * ray->raydir_y;
	else
		ray->wall_x = info->pos_x + ray->perpwall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	wall_get_texinfo(t_info *info, t_ray *ray, int x)
{
	int	t_width;
	int	t_height;
	int	y;

	t_width = info->texture[ray->tex_num].t_width;
	t_height = info->texture[ray->tex_num].t_width;
	ray->tex_x = (int)(ray->wall_x * (double)t_width);
	if (ray->side == 0 && ray->raydir_x < 0)
		ray->tex_x = t_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y > 0)
		ray->tex_x = t_width - ray->tex_x - 1;
	ray->step = 1.0 * t_height / ray->line_height;
	ray->tex_pos =
	(ray->drawstart - info->height / 2 + ray->line_height / 2) * ray->step;
	info->z_buffer[x] = ray->perpwall_dist;
	y = ray->drawstart;
	while (y < ray->drawend)
	{
		ray->tex_y =
		(int)ray->tex_pos > (t_height - 1) ? (t_height - 1) : (int)ray->tex_pos;
		ray->tex_pos += ray->step;
		info->buf[y][x] =
		info->texture[ray->tex_num].text[t_height * ray->tex_y + ray->tex_x];
		y++;
	}
}

void	draw_wall(t_info *info)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < info->width)
	{
		wall_init(info, &ray, x);
		wall_get_sidedist(info, &ray);
		wall_find_hit(info, &ray);
		wall_get_perp_drawline(info, &ray);
		wall_get_texinfo(info, &ray, x);
		x++;
	}
}
