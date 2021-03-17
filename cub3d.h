/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 09:01:11 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 23:48:31 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_AR_L 65361
# define K_AR_R 65363
# define K_ESC 65307
# define WALL_END 200

typedef struct	s_cub
{
	int				r_width;
	int				r_height;
	char			*no_text;
	char			*so_text;
	char			*we_text;
	char			*ea_text;
	char			*sp_text;
	int				c_colors[3];
	int				f_colors[3];
	int				c_color;
	int				f_color;
	t_list			*map_buffer;
	char			**map_array;
	int				map_row;
	unsigned int	map_col;
	int				player_x;
	int				player_y;
	char			player_dir;
	int				sprite_num;
	int				map_validity;
	char			*e_message;
	int				mode;
}				t_cub;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_text
{
	int			t_height;
	int			t_width;
	int			*text;
}				t_text;

typedef struct	s_key
{
	int		forward;
	int		backward;
	int		left;
	int		right;
	int		turn_left;
	int		turn_right;
}				t_key;

typedef struct	s_sprite
{
	int		x;
	int		y;
}				t_sprite;

typedef struct	s_sprites
{
	double				x;
	double				y;
	double				distance;
	struct s_sprites	*next;
}				t_sprites;

typedef struct	s_spinfo
{
	double	sprite_x;
	double	sprite_y;
	double	invdet;
	double	transform_x;
	double	transform_y;
	int		sp_screen_x;
	int		sp_height;
	int		sp_width;
	int		drawstart_y;
	int		drawend_y;
	int		drawstart_x;
	int		drawend_x;
	int		stripe;
	int		tex_x;
	int		tex_y;
}				t_spinfo;

typedef struct	s_info
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	t_img		img;
	t_cub		*map;
	int			map_row;
	char		**map_array;
	int			**buf;
	double		*z_buffer;
	t_text		*texture;
	double		mov_speed;
	double		rot_speed;
	int			width;
	int			height;
	int			f_color;
	int			c_color;
	t_key		*key;
	t_sprite	*sp_list;
	int			error;
}				t_info;

typedef struct	s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		drawstart;
	int		drawend;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}				t_ray;

int				get_next_line(int fd, char **line);
void			safe_free(void *ptr);
int				is_newline(char *save);
int				count_word_len(char *save);

int				check_cub(char *str);
t_cub			*map_init(void);
int				read_cub(char **av, t_cub *map);
int				get_resolution(char **line, char **ptr, t_cub *map);
char			*get_text_path(char **line, char **ptr,
				char *direction, char *text_path);
int				get_wall_texture(char **line, char **ptr, t_cub *map);
int				get_color(char **line, char **ptr, t_cub *map);
int				get_map(int fd, char **line, t_cub *map);
void			clear_map(char **map_array, int len);
void			check_map_wall(t_cub *map);
void			my_flood_fill(char **bp, int x, int y, t_cub *map);
void			skip_space(char **str);
int				get_kill_empty(int fd, char **line, char **ptr);
int				atoi_rev(char **fmt);
void			map_lstclear(t_list **lst);
void			map_lstclear_content(t_list **lst);

int				process_cast(t_cub *map, t_info *info);
void			set_screensize(t_cub *map, t_info *info);
int				init_info(t_cub *map, t_info *info);
void			copy_map_info(t_cub *map, t_info *info);
void			free_buf(int **buf, int size);
void			free_all(t_info *info);
int				get_textures(t_cub *map, t_info *info);
int				key_pressed(int key, t_info *info);
int				key_released(int key, t_info *info);
int				click_redcross(t_info *info);
void			turn_right(t_info *info);
void			turn_left(t_info *info);
void			player_move(t_info *info);
int				create_bmp(char	*filename, t_info *info);

void			draw(t_info *info);
void			draw_floor_ceiling(t_info *info);
void			draw_wall(t_info *info);
void			wall_init(t_info *info, t_ray *ray, int x);
void			wall_get_sidedist(t_info *info, t_ray *ray);
int				cast_sprites(t_info *info);
int				draw_sprites(t_info *info, t_sprites **head);

#endif
