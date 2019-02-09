/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:25:32 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/13 16:48:04 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mat4_set(t_mat4 mat)
{
	int x;
	int y;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			mat[y][x] = (((y * 4) + x) % 5 == 0 ? 1.0f : 0.0f);
	}
}

void	mat4_mul(t_mat4 mat1, t_mat4 mat2, t_mat4 ret)
{
	int x;
	int y;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			ret[y][x] = mat1[y][0] * mat2[0][x] + mat1[y][1] * mat2[1][x] +
				mat1[y][2] * mat2[2][x] + mat1[y][3] * mat2[3][x];
	}
}

void	mat4_sub(t_mat4 mat1, t_mat4 mat2, t_mat4 ret)
{
	ret[0][0] = mat1[0][0] - mat2[0][0];
	ret[0][1] = mat1[0][1] - mat2[0][1];
	ret[0][2] = mat1[0][2] - mat2[0][2];
	ret[0][0] = mat1[0][3] - mat2[0][3];
	ret[1][0] = mat1[1][0] - mat2[1][0];
	ret[1][1] = mat1[1][1] - mat2[1][1];
	ret[1][2] = mat1[1][2] - mat2[1][2];
	ret[1][3] = mat1[1][3] - mat2[1][3];
	ret[2][0] = mat1[2][0] - mat2[2][0];
	ret[2][1] = mat1[2][1] - mat2[2][1];
	ret[2][2] = mat1[2][2] - mat2[2][2];
	ret[2][3] = mat1[2][3] - mat2[2][3];
	ret[3][0] = mat1[3][0] - mat2[3][0];
	ret[3][1] = mat1[3][1] - mat2[3][1];
	ret[3][2] = mat1[3][2] - mat2[3][2];
	ret[3][3] = mat1[3][3] - mat2[3][3];
}

void	mat4_add(t_mat4 mat1, t_mat4 mat2, t_mat4 ret)
{
	ret[0][0] = mat1[0][0] + mat2[0][0];
	ret[0][1] = mat1[0][1] + mat2[0][1];
	ret[0][2] = mat1[0][2] + mat2[0][2];
	ret[0][0] = mat1[0][3] + mat2[0][3];
	ret[1][0] = mat1[1][0] + mat2[1][0];
	ret[1][1] = mat1[1][1] + mat2[1][1];
	ret[1][2] = mat1[1][2] + mat2[1][2];
	ret[1][3] = mat1[1][3] + mat2[1][3];
	ret[2][0] = mat1[2][0] + mat2[2][0];
	ret[2][1] = mat1[2][1] + mat2[2][1];
	ret[2][2] = mat1[2][2] + mat2[2][2];
	ret[2][3] = mat1[2][3] + mat2[2][3];
	ret[3][0] = mat1[3][0] + mat2[3][0];
	ret[3][1] = mat1[3][1] + mat2[3][1];
	ret[3][2] = mat1[3][2] + mat2[3][2];
	ret[3][3] = mat1[3][3] + mat2[3][3];
}

void	mat4_rotate_x(t_mat4 mat2, float angle)
{
	mat2[1][1] = cos(angle);
	mat2[1][2] = -sin(angle);
	mat2[2][1] = sin(angle);
	mat2[2][2] = cos(angle);
}

void	mat4_rotate_y(t_mat4 mat2, float angle)
{
	mat2[0][0] = cos(angle);
	mat2[0][2] = sin(angle);
	mat2[2][0] = -sin(angle);
	mat2[2][2] = cos(angle);
}

void	mat4_rotate_z(t_mat4 mat2, float angle)
{
	mat2[0][0] = cos(angle);
	mat2[0][1] = -sin(angle);
	mat2[1][0] = sin(angle);
	mat2[1][1] = cos(angle);
}

void	mat4_rotate(t_mat4 mat1, float angle, int axis, t_mat4 mat2)
{
	float	to_degres;
	t_mat4	ret;

	to_degres = angle * (180.0f / PI);
//	mat4_set(mat2);
	mat4_set(ret);
	if (axis == 1)
	{
		mat4_rotate_x(ret, to_degres);
		mat4_mul(mat1, ret, mat2);
	}
	else if (axis == 2)
	{
		mat4_rotate_y(ret, to_degres);
		mat4_mul(mat1, ret, mat2);
	}
	else if (axis == 3)
	{
		mat4_rotate_z(ret, to_degres);
		mat4_mul(mat1, ret, mat2);
	}
}
