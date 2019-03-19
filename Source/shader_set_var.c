/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_set_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:05:06 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/06 18:18:19 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			set_vec3_shader(GLint shader_program, char *name, t_vec4 vec)
{
	glUniform3f(glGetUniformLocation(shader_program, name),
		vec[0], vec[1], vec[2]);
}

void			set_vec2_shader(GLint shader_program, char *name, t_vec3 vec)
{
	glUniform2f(glGetUniformLocation(shader_program, name),
		vec[0], vec[1]);
}

void			set_mat4_shader(GLint shader_program, char *name, t_mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_program, name), 1,
		GL_TRUE, (const GLfloat *)mat);
}

void			set_int_shader(GLint shader_program, char *name, int integer)
{
	glUniform1f(glGetUniformLocation(shader_program, name), integer);
}
