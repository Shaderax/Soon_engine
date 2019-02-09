/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:12:34 by nrouzeva          #+#    #+#             */
/*   Updated: 2019/01/24 17:08:08 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	apply_view(t_mat4 viewe, t_vec4 x_asis, t_vec4 y_asis, t_vec4 dir)
{
	viewe[0][0] = x_asis[0];
	viewe[0][1] = x_asis[1];
	viewe[0][2] = x_asis[2];
	viewe[1][0] = y_asis[0];
	viewe[1][1] = y_asis[1];
	viewe[1][2] = y_asis[2];
	viewe[2][0] = dir[0];
	viewe[2][1] = dir[1];
	viewe[2][2] = dir[2];
	viewe[3][3] = 1;
}

void	set_view(t_vec4 pos, t_vec4 target, t_vec4 vec_y, t_mat4 view)
{
	t_mat4	viewe;
	t_mat4	mat;
	t_vec4	dir;
	t_vec4	x_asis;
	t_vec4	y_asis;

	mat4_set(viewe);
	vec4_sub(pos, target, dir);
	vec4_norm(dir);
	vec4_cross(vec_y, dir, x_asis);
	vec4_norm(x_asis);
	vec4_cross(dir, x_asis, y_asis);
	apply_view(viewe, x_asis, y_asis, dir);
	mat4_set(mat);
	mat[0][3] = -pos[0];
	mat[1][3] = -pos[1];
	mat[2][3] = -pos[2];
	mat4_mul(viewe, mat, view);
}

void	new_view(t_camera *camera, float cam_speed)
{
	t_vec4 sub;

	camera->speed = cam_speed;
	mat4_set(camera->view);
	vec4_set(sub, (t_vec4){0.0f, 0.0f, 0.0f, 0.0f});
	vec4_set(camera->pos, (t_vec4){0.0f, 1.0f, 0.5f, 0.0f});
	vec4_set(camera->target, (t_vec4){0.0f, 0.0f, -1.0f, 0.0f});
	vec4_set(camera->rotate, (t_vec4){0.0f, 1.0f, 0.0f, 0.0f});
	vec4_sub(camera->pos, camera->target, sub);
	set_view(camera->pos, sub, camera->rotate, camera->view);
}
