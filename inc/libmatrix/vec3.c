/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:38:59 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/01 18:13:33 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	vec3_add(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3)
{
	int index;

	index = -1;
	while (++index < 3)
		vector3[index] = vector1[index] + vector2[index];
}

void	vec3_sub(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3)
{
	int index;

	index = -1;
	while (++index < 3)
		vector3[index] = vector1[index] - vector2[index];
}

void	vec3_cross(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3)
{
	vector3[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	vector3[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	vector3[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

float	vec3_distance(t_vec3 v)
{
	return (sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])));
}

void	vec3_norm(t_vec3 vec)
{
	int		index;
	float	dist;

	dist = vec3_distance(vec);
	if (dist == 0)
		return ;
	index = -1;
	while (++index < 3)
		vec[index] /= dist;
}
