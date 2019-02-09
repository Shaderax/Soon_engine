/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:00:05 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/01 18:12:58 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	vec4_add(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3)
{
	int index;

	index = -1;
	while (++index < 3)
		vector3[index] = vector1[index] + vector2[index];
	vector1[3] = 0;
}

void	vec4_sub(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3)
{
	int index;

	index = -1;
	while (++index < 3)
		vector3[index] = vector1[index] - vector2[index];
	vector3[3] = 0;
}

float	vec4_distance(t_vec4 v)
{
	return (sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])));
}

void	vec4_norm(t_vec4 vec)
{
	int		index;
	float	dist;

	dist = vec4_distance(vec);
	if (dist == 0)
		return ;
	index = -1;
	while (++index < 3)
		vec[index] /= dist;
}

void	vec4_cross(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3)
{
	vector3[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	vector3[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	vector3[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
	vector3[3] = vector1[3];
}

void	vec4_set(t_vec4 vector1, t_vec4 vector2)
{
	vector1[0] = vector2[0];
	vector1[1] = vector2[1];
	vector1[2] = vector2[2];
	vector1[3] = vector2[3];
}

void	vec4_mul_scal(t_vec4 vec, float i, t_vec4 ret)
{
	ret[0] = vec[0] * i;
	ret[1] = vec[1] * i;
	ret[2] = vec[2] * i;
	ret[3] = 0;
}
