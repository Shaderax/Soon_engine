/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:23:23 by nrouzeva          #+#    #+#             */
/*   Updated: 2019/01/24 15:08:33 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
/*
   void	set_mouse_win(t_window *win)
   {
   glfwSetInputMode(win->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   bzero(&(win->mouse), sizeof(t_mouse));
   glfwGetCursorPos(win->win, &win->mouse.new_x, &win->mouse.new_y);
   win->mouse.last_x = win->mouse.new_x;
   win->mouse.last_y = win->mouse.new_y;
   win->mouse.sensitivity = 0.1f;
   win->mouse.yaw = -90.0f;
   win->mouse.pitch = 0.0f;
   }

   int		mouse_moved(t_mouse *mouse)
   {
   if (mouse->new_x != mouse->last_x || mouse->new_y != mouse->last_y)
   return (1);
   return (0);
   }

   void	mouse_move(t_window *window, t_camera *camera)
   {
   glfwGetCursorPos(window->win, &window->mouse.new_x, &window->mouse.new_y);
   if (mouse_moved(&(window->mouse)) == 0)
   return ;
   window->mouse.off_x = window->mouse.new_x - window->mouse.last_x;
   window->mouse.off_y = window->mouse.new_y - window->mouse.last_y;
   window->mouse.last_x = window->mouse.new_x;
   window->mouse.last_y = window->mouse.new_y;
   window->mouse.off_x *= window->mouse.sensitivity;
   window->mouse.off_y *= window->mouse.sensitivity;
   window->mouse.yaw += window->mouse.off_x;
   window->mouse.pitch += window->mouse.off_y;
   if (window->mouse.pitch > 89.0f)
   window->mouse.pitch = 89.0f;
   if (window->mouse.pitch < -89.0f)
   window->mouse.pitch = -89.0f;
   camera->target[0] = cos(window->mouse.yaw * (PI / 180)) *
   cos(window->mouse.pitch * (PI / 180));
   camera->target[1] = -sin(window->mouse.pitch * (PI / 180));
   camera->target[2] = sin(window->mouse.yaw * (PI / 180)) *
   cos(window->mouse.pitch * (PI / 180));
   camera->target[3] = 0;
   vec4_norm(camera->target);
   }
*/

Mouse::Mouse( Window *window )
{
	bzero(this, sizeof(Mouse));
	glfwSetInputMode(window->_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window->_win, &new_x, &new_y);
	last_x = new_x;
	last_y = new_y;
	sensitivity = 0.1f;
	yaw = -90.0f;
	pitch = 0.0f;
}

Mouse::~Mouse( void )
{

}

int Mouse::mouseMoved( void )
{
	if (new_x != last_x || new_y != last_y)
		return (1);
	return (0);
}
