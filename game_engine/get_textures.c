/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 00:27:43 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 21:33:10 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_each_pixel(t_text *texture, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture->text[img->img_width * y + x] =
			img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
}

int		get_each_texture(t_info *info, t_text *texture, char *path, t_img *img)
{
	int i;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width,
	&img->img_height);
	if (!img->img)
		return (-1);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l,
	&img->endian);
	texture->t_height = img->img_height;
	texture->t_width = img->img_width;
	texture->text =
	(int *)malloc(sizeof(int) * (texture->t_height * texture->t_width));
	i = 0;
	while (i < (texture->t_height * texture->t_width))
		texture->text[i++] = 0;
	get_each_pixel(texture, img);
	mlx_destroy_image(info->mlx, img->img);
	return (0);
}

int		get_textures(t_cub *map, t_info *info)
{
	t_img	img;

	if (get_each_texture(info, &(info->texture[0]), map->no_text, &img) == -1)
		return (-1);
	if (get_each_texture(info, &(info->texture[1]), map->so_text, &img) == -1)
		return (-1);
	if (get_each_texture(info, &(info->texture[2]), map->ea_text, &img) == -1)
		return (-1);
	if (get_each_texture(info, &(info->texture[3]), map->we_text, &img) == -1)
		return (-1);
	if (get_each_texture(info, &(info->texture[4]), map->sp_text, &img) == -1)
		return (-1);
	return (0);
}
