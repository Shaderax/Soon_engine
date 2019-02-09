/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:58:37 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/07 11:46:27 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	load_texture(char *path, t_texture *obj_txt)
{
	unsigned char	buf[4096];
	int		fd;
	int		count;
	int		ret;
	int		index;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	read(fd, buf, 54);
	obj_txt->width = *(int*)(buf + 18);
	obj_txt->height = *(int*)(buf + 22);
	obj_txt->size = *(int*)(buf + 2) - 14 - *(int*)(buf + 14);
	obj_txt->data = malloc(obj_txt->size);
	read(fd, buf, *(int*)(buf + 14) - 40);
	count = 0;
	while ((ret = read(fd, buf, 4096)))
	{
		index = -1;
		while (++index < ret)
			obj_txt->data[count + index] = buf[index];
		count += ret;
	}
	return (1);
}

int	new_obj_texture(char *path, t_texture *obj_txt)
{
	if (load_texture(path, obj_txt) == -1)
		return (-1);
	glGenTextures(1, &obj_txt->txt);
	glBindTexture(GL_TEXTURE_2D, obj_txt->txt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, obj_txt->width, obj_txt->height,
		0, GL_BGR, GL_UNSIGNED_BYTE, obj_txt->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (1);
}
