/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:32:47 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/06 16:19:27 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		delete_object(t_object obj)
{
	glDeleteVertexArrays(1, &obj.vao);
	//	glDeleteBuffers(1, &obj.vbo);
}

void		set_vao(t_object *object)
{
	new_buffer(&(object->vertex_array));
	if (object->normal_array.size)
		new_buffer(&(object->normal_array));
	if (object->texture_coord.size)
		new_buffer(&(object->texture_coord));
	mat4_set(object->translate);
	mat4_set(object->rotate);
	mat4_set(object->scale);
	glGenVertexArrays(1, &(object->vao));
	glBindVertexArray(object->vao);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertex_array.vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	if (object->normal_array.size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, object->normal_array.vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
	}
	if (object->texture_coord.size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, object->texture_coord.vbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
	}
}

t_object	new_object(char *path)
{
	t_object	object;

	bzero(&object, sizeof(t_object));
	parse_obj_file(path, &object);
	set_vao(&object);

	return (object);
}

void		compute_model(t_object *obj)
{
	t_mat4 prout;

	mat4_mul(obj->translate, obj->rotate, prout);
	mat4_mul(prout, obj->scale, obj->model);
}

void		compute_mvp(t_object *obj, t_camera *cam)
{
	t_mat4 prout;

	mat4_mul(cam->proj, cam->view, prout);
	mat4_mul(prout, obj->model, obj->mvp);
}
