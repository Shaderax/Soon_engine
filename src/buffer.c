/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:29:21 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/04 15:32:58 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	new_buffer(t_buffer *buf)
{
	glGenBuffers(1, &(buf->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, buf->vbo);
	glBufferData(GL_ARRAY_BUFFER, buf->size * sizeof(float),
		buf->array, GL_STATIC_DRAW);
}
