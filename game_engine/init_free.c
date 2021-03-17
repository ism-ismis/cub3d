/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:58:45 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 23:25:37 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	define_dir_plane(t_info *info, double dirx, double diry, double planex)
{
	info->dir_x = dirx;
	info->dir_y = diry;
	info->plane_x = planex;
}

void	copy_map_info(t_cub *map, t_info *info)
{
	if (map->player_dir == 'N')
	{
		define_dir_plane(info, 0.0, -1.0, 0.66);
		info->plane_y = 0.0;
	}
	else if (map->player_dir == 'S')
	{
		define_dir_plane(info, 0.0, 1.0, -0.66);
		info->plane_y = 0.0;
	}
	else if (map->player_dir == 'E')
	{
		define_dir_plane(info, 1.0, 0.0, 0.0);
		info->plane_y = 0.66;
	}
	else if (map->player_dir == 'W')
	{
		define_dir_plane(info, -1.0, 0.0, 0.0);
		info->plane_y = -0.66;
	}
}

void	free_buf(int **buf, int size)
{
	size = (size - 1 < 0) ? size : size - 1;
	while (0 <= size)
	{
		safe_free(buf[size]);
		size--;
	}
	free(buf);
}

void	free_texture(t_info *info, int size)
{
	int	i;

	if (info->texture)
	{
		i = 0;
		while (i < size)
		{
			safe_free(info->texture[i].text);
			i++;
		}
		safe_free(info->texture);
	}
}

void	free_all(t_info *info)
{
	free_buf(info->buf, info->height);
	free_texture(info, 5);
	safe_free(info->key);
	safe_free(info->sp_list);
	safe_free(info->z_buffer);
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		mlx_destroy_display(info->mlx);
	safe_free(info->mlx);
	safe_free(info);
}
