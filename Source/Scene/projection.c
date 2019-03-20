/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:26:25 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/04 17:13:02 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_projection_matrix(float fov, float ratio, t_camera *cam)
{
	float scale;
	float l;
	float r;
	float b;
	float t;

	scale = tan(fov * 0.5 * (PI / 180)) * cam->near;
	t = scale;
	b = -scale;
	r = scale * ratio;
	l = -r;
	cam->proj[0][0] = (2 * cam->near) / (r - l);
	cam->proj[0][2] = (r + l) / (r - l);
	cam->proj[1][1] = (2 * cam->near) / (t - b);
	cam->proj[1][2] = (t + b) / (t - b);
	cam->proj[2][2] = -((cam->far + cam->near) / (cam->far - cam->near));
	cam->proj[2][3] = -((2 * cam->far * cam->near) / (cam->far - cam->near));
	cam->proj[3][2] = -1;
}

void	new_projection_matrix(float fov, float ratio, t_camera *cam)
{
	mat4_set(cam->proj);
	cam->near = NEAR;
	cam->far = FAR;
	set_projection_matrix(fov, ratio, cam);
}
