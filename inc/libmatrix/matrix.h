/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:42:06 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/03 17:36:30 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "math.h"

# define PI 3.14159265359

typedef float	t_mat3[3][3];
typedef float	t_mat4[4][4];

typedef float	t_vec3[3];
typedef float	t_vec4[4];

void	vec3_add(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3);
void	vec3_sub(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3);
void	vec3_cross(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3);
void	vec3_norm(t_vec3 vec);

void	vec4_add(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void	vec4_sub(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void	vec4_mul(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void	vec4_cross(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void	vec4_norm(t_vec4 vec);
void	vec4_set(t_vec4 vector1, t_vec4 vector2);
void	vec4_mul_scal(t_vec4 vec, float i, t_vec4 ret);

void	mat4_set(t_mat4 mat);
void	mat4_mul(t_mat4 mat1, t_mat4 mat2, t_mat4 ret);
void	mat4_sub(t_mat4 mat1, t_mat4 mat2, t_mat4 ret);
void	mat4_add(t_mat4 mat1, t_mat4 mat2, t_mat4 ret);
void	mat4_translate(t_mat4 mat1, t_vec4 vec, t_mat4 mat2);
void	mat4_rotate(t_mat4 mat1, float angle, int axis, t_mat4 mat2);
#endif
