/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:34:01 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/15 10:57:52 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	move_cam_x(t_window *window, t_camera *camera)
{
	t_vec4	ret;

	if (glfwGetKey(window->win, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec4_cross(camera->target, camera->rotate, ret);
		vec4_norm(ret);
		vec4_mul_scal(ret, camera->speed, ret);
		vec4_sub(camera->pos, ret, camera->pos);
	}
	if (glfwGetKey(window->win, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec4_cross(camera->target, camera->rotate, ret);
		vec4_norm(ret);
		vec4_mul_scal(ret, camera->speed, ret);
		vec4_add(camera->pos, ret, camera->pos);
	}
}

void	move_cam_y(t_window *window, t_camera *camera)
{
	t_vec4	ret;

	if (glfwGetKey(window->win, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		vec4_mul_scal(camera->rotate, camera->speed, ret);
		vec4_add(camera->pos, ret, camera->pos);
	}
	if (glfwGetKey(window->win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		vec4_mul_scal(camera->rotate, camera->speed, ret);
		vec4_sub(camera->pos, ret, camera->pos);
	}
}

void	move_cam_z(t_window *window, t_camera *camera)
{
	t_vec4	ret;

	if (glfwGetKey(window->win, GLFW_KEY_W) == GLFW_PRESS)
	{
		vec4_mul_scal(camera->target, camera->speed, ret);
		vec4_add(camera->pos, ret, camera->pos);
	}
	if (glfwGetKey(window->win, GLFW_KEY_S) == GLFW_PRESS)
	{
		vec4_mul_scal(camera->target, camera->speed, ret);
		vec4_sub(camera->pos, ret, camera->pos);
	}
}

void	light_control(t_window *window, t_light *spot)
{
	float light_s = 0.1f;
	if (glfwGetKey(window->win, GLFW_KEY_LEFT) == GLFW_PRESS)
		spot->pos[0] -= light_s;
	if (glfwGetKey(window->win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		spot->pos[0] += light_s;
	if (glfwGetKey(window->win, GLFW_KEY_UP) == GLFW_PRESS)
		spot->pos[2] -= light_s;
	if (glfwGetKey(window->win, GLFW_KEY_DOWN) == GLFW_PRESS)
		spot->pos[2] += light_s;
	if (glfwGetKey(window->win,GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		spot->pos[1] += light_s;
	if (glfwGetKey(window->win,GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		spot->pos[1] -= light_s;
}

void	cam_control(t_window *window, t_camera *camera)
{
	move_cam_x(window, camera);
	move_cam_y(window, camera);
	move_cam_z(window, camera);
}

void	input_control(t_window *window, t_scene *scene)
{
	if (glfwGetKey(window->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->win, TRUE);
	if (glfwGetKey(window->win, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS)
		scene->camera.speed += 0.01;
	if (glfwGetKey(window->win, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		scene->camera.speed -= 0.01;
	cam_control(window, &scene->camera);
	light_control(window, &scene->spot);
	mouse_move(window, &scene->camera);
}
