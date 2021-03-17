/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 23:14:12 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 11:11:40 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_valid_char(int c)
{
	if (!(c == ' ' || c == '0' || c == '1' || c == '2'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (0);
	return (1);
}

int		check_format_count_sprite(t_cub *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_row)
	{
		j = 0;
		while (map->map_array[i][j])
		{
			if (!(is_valid_char(map->map_array[i][j])))
			{
				map->e_message = "Invalid character is used in the map.";
				return (-1);
			}
			if (map->map_array[i][j] == '2')
				map->sprite_num++;
			if (map->map_array[i][j] == ' ')
				map->map_array[i][j] = 'x';
			j++;
		}
		i++;
	}
	return (0);
}

void	check_map_array(t_cub *map)
{
	if (map->map_row > WALL_END - 2 || map->map_col > WALL_END - 2)
	{
		map->e_message = "Map is too big.";
		return ;
	}
	if (check_format_count_sprite(map) == -1)
		return ;
	check_map_wall(map);
}

void	copy_map_array(t_cub *map)
{
	int		i;
	t_list	*list_p;

	map->map_row = ft_lstsize(map->map_buffer);
	if (!(map->map_array = malloc(sizeof(char *) * (map->map_row))))
	{
		map_lstclear_content(&map->map_buffer);
		map->e_message = "Fail to launch the game.";
		return ;
	}
	i = 0;
	list_p = map->map_buffer;
	while (i < map->map_row)
	{
		map->map_array[i] = (char *)map->map_buffer->content;
		map->map_col = map->map_col > ft_strlen(map->map_array[i])
		? map->map_col : ft_strlen(map->map_array[i]);
		i++;
		map->map_buffer = map->map_buffer->next;
	}
	map_lstclear(&list_p);
}

int		get_map(int fd, char **line, t_cub *map)
{
	get_next_line(fd, line);
	while (**line == '\0')
	{
		safe_free(*line);
		get_next_line(fd, line);
	}
	if (!(map->map_buffer = ft_lstnew(ft_strdup(*line))))
	{
		safe_free(*line);
		return (-1);
	}
	safe_free(*line);
	while ((get_next_line(fd, line)) > 0)
	{
		ft_lstadd_back(&map->map_buffer, ft_lstnew(ft_strdup(*line)));
		safe_free(*line);
	}
	safe_free(*line);
	copy_map_array(map);
	check_map_array(map);
	if (map->e_message)
		return (-1);
	return (0);
}
