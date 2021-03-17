/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:54:13 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 11:08:38 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	surround_x(char **bp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < WALL_END)
		bp[i][j++] = 'x';
	j--;
	while (i < WALL_END)
		bp[i++][j] = 'x';
	i--;
	while (j >= 0)
		bp[i][j--] = 'x';
	j++;
	while (i >= 0)
		bp[i--][j] = 'x';
}

char	**create_map_wall(char **bp)
{
	int i;
	int j;

	i = 0;
	bp = (char **)malloc(sizeof(char *) * (WALL_END));
	while (i < WALL_END)
		*(bp + (i++)) = (char *)malloc(WALL_END + 1);
	i = 0;
	while (i < WALL_END)
	{
		j = 0;
		while (j < WALL_END)
			bp[i][j++] = '0';
		i++;
	}
	surround_x(bp);
	return (bp);
}

void	define_player(t_cub *map, int *count, int i, int j)
{
	if (*count == 0)
	{
		map->player_x = j;
		map->player_y = i;
		map->player_dir = map->map_array[i][j];
		map->map_array[i][j] = '0';
		*count = 1;
	}
	else
		map->e_message = "Number of player must be one.";
}

void	find_player(t_cub *map)
{
	int	i;
	int	j;
	int count;

	count = 0;
	i = 0;
	while (i < map->map_row)
	{
		j = 0;
		while (map->map_array[i][j])
		{
			if (map->map_array[i][j] == 'N' || map->map_array[i][j] == 'S'
			|| map->map_array[i][j] == 'W' || map->map_array[i][j] == 'E')
				define_player(map, &count, i, j);
			j++;
		}
		i++;
	}
}

void	check_map_wall(t_cub *map)
{
	char	**bp;
	int		i;
	int		j;

	find_player(map);
	if (map->e_message)
		return ;
	bp = NULL;
	bp = create_map_wall(bp);
	i = 0;
	while (i < map->map_row)
	{
		j = 0;
		while (map->map_array[i][j])
		{
			bp[i + 1][j + 1] = map->map_array[i][j];
			j++;
		}
		i++;
	}
	my_flood_fill(bp, map->player_x + 1, map->player_y + 1, map);
	clear_map(bp, WALL_END);
	if (map->map_validity)
		map->e_message = "Invalid format of the map.";
}
