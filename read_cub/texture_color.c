/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 23:32:06 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 23:27:03 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_resolution(char **line, char **ptr, t_cub *map)
{
	if (map->r_width != -2)
	{
		map->e_message = "Invalid format of the cub file.";
		safe_free(*line);
		return (-1);
	}
	(*ptr)++;
	skip_space(ptr);
	map->r_width = atoi_rev(ptr);
	skip_space(ptr);
	map->r_height = atoi_rev(ptr);
	if (map->r_width <= 0 || map->r_height <= 0)
		map->e_message = "Invalid format of resolution.";
	skip_space(ptr);
	if (**ptr != '\0')
		map->e_message = "Invalid format of the cub file.";
	safe_free(*line);
	if (map->e_message)
		return (-1);
	return (0);
}

char	*get_text_path(char **line, char **ptr,
char *direction, char *text_path)
{
	char	*text;

	if (text_path)
	{
		safe_free(text_path);
		safe_free(*line);
		return (NULL);
	}
	if (!(ft_strncmp(*ptr, direction, 2)))
		*ptr += 2;
	else
		(*ptr)++;
	skip_space(ptr);
	text = ft_strdup(*ptr);
	safe_free(*line);
	return (text);
}

int		get_wall_texture(char **line, char **ptr, t_cub *map)
{
	if (!(ft_strncmp(*ptr, "NO", 2)))
	{
		if (!(map->no_text = get_text_path(line, ptr, "NO", map->no_text)))
			map->e_message = "Invalid format of the cub file.";
	}
	else if (!(ft_strncmp(*ptr, "SO", 2)))
	{
		if (!(map->so_text = get_text_path(line, ptr, "SO", map->so_text)))
			map->e_message = "Invalid format of the cub file.";
	}
	else if (!(ft_strncmp(*ptr, "WE", 2)))
	{
		if (!(map->we_text = get_text_path(line, ptr, "WE", map->we_text)))
			map->e_message = "Invalid format of the cub file.";
	}
	else if (!(ft_strncmp(*ptr, "EA", 2)))
	{
		if (!(map->ea_text = get_text_path(line, ptr, "EA", map->ea_text)))
			map->e_message = "Invalid format of the cub file.";
	}
	if (map->e_message)
		return (-1);
	return (0);
}

void	get_each_color(char **ptr, int *map_color, t_cub *map)
{
	int	i;

	i = 0;
	(*ptr)++;
	skip_space(ptr);
	while (i < 3)
	{
		if (i > 0 && **ptr == ',')
			(*ptr)++;
		skip_space(ptr);
		if (**ptr >= '0' && **ptr <= '9')
			map_color[i] = atoi_rev(ptr);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (map_color[i] < 0 || map_color[i] > 255)
			map->e_message = "Invalid format of the cub file.";
		i++;
	}
	skip_space(ptr);
	if (**ptr)
		map->e_message = "Invalid format of the cub file.";
}

int		get_color(char **line, char **ptr, t_cub *map)
{
	if (**ptr == 'F')
	{
		if (map->f_colors[0] != -2)
			map->e_message = "Invalid format of the cub file.";
		else
			get_each_color(ptr, map->f_colors, map);
	}
	else if (**ptr == 'C')
	{
		if (map->c_colors[0] != -2)
			map->e_message = "Invalid format of the cub file.";
		else
			get_each_color(ptr, map->c_colors, map);
	}
	safe_free(*line);
	if (map->e_message)
		return (-1);
	return (0);
}
