/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:50:22 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/22 15:03:13 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_init2(t_cub *map)
{
	map->map_buffer = NULL;
	map->map_array = NULL;
	map->map_row = 0;
	map->map_col = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
	map->sprite_num = 0;
	map->map_validity = 0;
	map->e_message = NULL;
	map->mode = 0;
}

t_cub	*map_init(void)
{
	t_cub	*map;
	int		i;

	if (!(map = (t_cub *)malloc(sizeof(t_cub))))
		return (NULL);
	map->r_width = -2;
	map->r_height = -2;
	map->no_text = NULL;
	map->so_text = NULL;
	map->we_text = NULL;
	map->ea_text = NULL;
	map->sp_text = NULL;
	i = 0;
	while (i < 3)
		map->c_colors[i++] = -2;
	i = 0;
	while (i < 3)
		map->f_colors[i++] = -2;
	map->c_color = -2;
	map->f_color = -2;
	map_init2(map);
	return (map);
}

void	clear_map(char **map_array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		safe_free(map_array[i]);
		i++;
	}
	free(map_array);
	map_array = NULL;
}

void	my_flood_fill(char **bp, int x, int y, t_cub *map)
{
	if (bp[y][x] != 'N' && bp[y][x] != 'S'
	&& bp[y][x] != 'W' && bp[y][x] != 'E')
		bp[y][x] = 'C';
	if (bp[y - 1][x] == 'x' || bp[y + 1][x] == 'x'
	|| bp[y][x - 1] == 'x' || bp[y][x + 1] == 'x')
	{
		map->map_validity = 1;
		return ;
	}
	if (bp[y - 1][x] == '0')
		my_flood_fill(bp, x, y - 1, map);
	if (bp[y][x + 1] == '0')
		my_flood_fill(bp, x + 1, y, map);
	if (bp[y + 1][x] == '0')
		my_flood_fill(bp, x, y + 1, map);
	if (bp[y][x - 1] == '0')
		my_flood_fill(bp, x - 1, y, map);
}
