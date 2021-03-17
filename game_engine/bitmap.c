/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:37:45 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 11:19:18 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	write_img_data(int fd, t_info *info, int cal_width,
		unsigned char *img_data)
{
	int i;
	int j;

	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width)
		{
			img_data[j * 3] = (info->buf[info->height - i - 1][j] & 0xFF);
			img_data[j * 3 + 1] =
			((info->buf[info->height - i - 1][j] & (0xFF << 8)) >> 8);
			img_data[j * 3 + 2] =
			((info->buf[info->height - i - 1][j] & (0xFF << 16)) >> 16);
			j++;
		}
		j = info->width * 3;
		while (j < cal_width)
			img_data[j++] = 0;
		write(fd, img_data, sizeof(unsigned char) * cal_width);
		i++;
	}
}

int		get_img_data(int fd, t_info *info, int cal_width)
{
	unsigned char	*img_data;

	if (!(img_data =
	(unsigned char *)malloc(sizeof(unsigned char) * cal_width)))
		return (-1);
	write_img_data(fd, info, cal_width, img_data);
	safe_free(img_data);
	return (0);
}

void	get_info_header(int fd, t_info *info, int cal_width)
{
	unsigned long	info_header_size;
	unsigned int	planes;
	unsigned int	color_bpp;
	unsigned long	data_size;

	info_header_size = 40;
	planes = 1;
	color_bpp = 24;
	data_size = info->height * cal_width;
	write(fd, &info_header_size, 4);
	write(fd, &info->width, 4);
	write(fd, &info->height, 4);
	write(fd, &planes, 2);
	write(fd, &color_bpp, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &data_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
}

int		create_bmp(char *filename, t_info *info)
{
	int				res;
	int				fd;
	int				cal_width;
	unsigned int	file_size;
	unsigned int	pixel_data_offset;

	if ((fd = open(filename, O_CREAT | O_RDWR, S_IRWXU)))
	{
		cal_width = info->width * 3 + info->width % 4;
		file_size = info->height * cal_width + 14 + 40;
		pixel_data_offset = 14 + 40;
		write(fd, "BM", 2);
		write(fd, &file_size, 4);
		write(fd, "\0\0\0\0", 4);
		write(fd, &pixel_data_offset, 4);
		get_info_header(fd, info, cal_width);
		res = get_img_data(fd, info, cal_width);
		close(fd);
		return (res);
	}
	else
		return (-1);
}
