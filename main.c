/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:43:37 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 23:27:04 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		prepare_read_cub(int ac, char **av, t_cub **map)
{
	if (ac < 2 || ac > 3 || (ac == 3 && ft_strncmp(av[2], "--save", 7)))
	{
		printf("Error\nNumber or content of arguments is invalid.\n");
		return (-1);
	}
	if (!(*map = map_init()))
	{
		printf("Error\nFail to launch the game.\n");
		return (-1);
	}
	if ((check_cub(av[1]) == -1))
	{
		(*map)->e_message = "The file name is invalid.";
		return (-1);
	}
	return (0);
}

void	free_map(t_cub *map)
{
	if (map->map_array)
		clear_map(map->map_array, map->map_row);
	safe_free(map->no_text);
	safe_free(map->so_text);
	safe_free(map->ea_text);
	safe_free(map->we_text);
	safe_free(map->sp_text);
	safe_free(map);
}

int		main(int ac, char **av)
{
	t_cub	*map;
	t_info	info;

	map = NULL;
	if (prepare_read_cub(ac, av, &map) == 0)
	{
		if (ac == 3)
			map->mode = 1;
		read_cub(&av[1], map);
		if (!map->e_message)
		{
			if (process_cast(map, &info) == -1)
				map->e_message = "Fail to launch the game.";
		}
	}
	if (map && map->e_message)
		printf("Error\n%s\n", map->e_message);
	if (map)
		free_map(map);
	return (0);
}
