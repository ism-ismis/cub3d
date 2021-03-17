/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:36:13 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 17:44:38 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_screensize(t_cub *map, t_info *info)
{
	int sizex;
	int sizey;

	sizex = 0;
	sizey = 0;
	mlx_get_screen_size(info->mlx, &sizex, &sizey);
	if (map->r_width < sizex)
		info->width = map->r_width;
	else
		info->width = sizex;
	if (map->r_height < sizey)
		info->height = map->r_height;
	else
		info->height = sizey;
}

void	calc(t_info *info)
{
	draw_floor_ceiling(info);
	draw_wall(info);
	if (info->map->sprite_num > 0)
	{
		if (cast_sprites(info) == -1)
			mlx_loop_end(info->mlx);
	}
}

int		main_loop(t_info *info)
{
	calc(info);
	draw(info);
	player_move(info);
	return (0);
}

int		play_game(t_info *info)
{
	if (!(info->win = mlx_new_window(info->mlx, info->width, info->height,
	"cub3D")))
		return (-1);
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp,
	&info->img.size_l, &info->img.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, 2, 1L << 0, &key_pressed, info);
	mlx_hook(info->win, 3, 1L << 1, &key_released, info);
	mlx_hook(info->win, 33, 1L << 17, &click_redcross, info);
	mlx_loop(info->mlx);
	return (0);
}

int		process_cast(t_cub *map, t_info *info)
{
	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (-1);
	info->mlx = mlx_init();
	set_screensize(map, info);
	if (init_info(map, info) == -1)
		return (-1);
	if (get_textures(map, info) == -1)
	{
		map->e_message = "Cannot read texture file.";
		free_all(info);
		return (-2);
	}
	if (!map->mode)
	{
		if (play_game(info) == -1)
			return (-1);
	}
	else
	{
		calc(info);
		create_bmp("cub3D.bmp", info);
	}
	free_all(info);
	return (0);
}
