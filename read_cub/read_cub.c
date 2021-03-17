/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 23:30:54 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 18:45:58 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_cub(char *str)
{
	if ((ft_strlen(str) <= 4))
		return (-1);
	while (*str != '.')
	{
		if (!ft_strncmp(str, "/.cub", 5))
			return (-1);
		str++;
	}
	if ((ft_strncmp(str, ".cub", 4)))
		return (-1);
	str += 4;
	if (*str)
		return (-1);
	return (0);
}

int		read_elements2(char **line, char **ptr, t_cub *map)
{
	if (**ptr == 'R')
		get_resolution(line, ptr, map);
	else if (!(ft_strncmp(*ptr, "NO", 2) && ft_strncmp(*ptr, "SO", 2)
	&& ft_strncmp(*ptr, "WE", 2) && ft_strncmp(*ptr, "EA", 2)))
		get_wall_texture(line, ptr, map);
	else if (**ptr == 'S')
	{
		if (!(map->sp_text = get_text_path(line, ptr, "s", map->sp_text)))
			map->e_message = "Invalid format of the cub file.";
	}
	else if (**ptr == 'F' || **ptr == 'C')
		get_color(line, ptr, map);
	else
	{
		map->e_message = "Invalid format of the cub file.";
		safe_free(*line);
	}
	if (map->e_message)
		return (-1);
	return (0);
}

int		read_elements(int fd, char **line, char **ptr, t_cub *map)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (get_kill_empty(fd, line, ptr) == -1)
		{
			map->e_message = "Fail to read a file.";
			return (-1);
		}
		if (read_elements2(line, ptr, map) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	create_trgb(t_cub *map)
{
	map->f_color = (0 << 24 | map->f_colors[0] << 16
	| map->f_colors[1] << 8 | map->f_colors[2]);
	map->c_color = (0 << 24 | map->c_colors[0] << 16
	| map->c_colors[1] << 8 | map->c_colors[2]);
}

int		read_cub(char **av, t_cub *map)
{
	int		fd;
	char	*line;
	char	*ptr;

	if ((fd = open(*av, O_RDONLY)) >= 0)
	{
		line = NULL;
		if (read_elements(fd, &line, &ptr, map) == -1)
			return (-1);
		create_trgb(map);
		if (get_map(fd, &line, map) == -1)
			return (-1);
		close(fd);
		return (0);
	}
	map->e_message = "Fail to read a file.";
	return (-1);
}
