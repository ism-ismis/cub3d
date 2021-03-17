/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:47:44 by ishirais          #+#    #+#             */
/*   Updated: 2021/02/24 21:08:21 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*buf_add(char *save, char *buf)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	len = ft_strlen(buf);
	if (save)
		len += ft_strlen(save);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (save && save[i])
	{
		str[i] = save[i];
		i++;
	}
	while (i + j < len)
	{
		str[i + j] = buf[j];
		j++;
	}
	str[len] = '\0';
	safe_free(save);
	return (str);
}

char	*get_line(char *save, char **line)
{
	int		i;
	char	*res;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		res[i] = save[i];
		i++;
	}
	res[i] = '\0';
	if (!res)
	{
		safe_free(save);
		*line = NULL;
	}
	return (res);
}

char	*get_new_save(char *save, char **line)
{
	int		i;
	int		len;
	char	*res;

	i = count_word_len(save);
	len = 0;
	while (save[i + len])
		len++;
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	len = 0;
	while (save[i + len])
	{
		res[len] = save[i + len];
		len++;
	}
	res[len] = '\0';
	safe_free(save);
	if (!res)
		*line = NULL;
	return (res);
}

int		check_read_len(char **line, int read_len, char *save)
{
	if (read_len == 0)
	{
		safe_free(save);
		*line = ft_strdup("");
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			read_len;
	char		buf[5000];
	static char	*save;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	read_len = 1;
	while (read_len && !(is_newline(save)))
	{
		if ((read_len = read(fd, buf, 4999)) < 0)
			return (-1);
		buf[read_len] = '\0';
		if (!(save = buf_add(save, buf)))
			return (-1);
	}
	if (check_read_len(line, read_len, save) == 0)
		return (0);
	if (!(*line = get_line(save, line)))
		return (-1);
	if (!(save = get_new_save(save, line)))
		return (-1);
	return (1);
}
