/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:19:28 by nrouzeva          #+#    #+#             */
/*   Updated: 2019/01/24 18:59:06 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
   t_window	new_window(int width, int height, char *name_window)
   {
   t_window screen;

   screen.width = width;
   screen.height = height;
   screen.win = glfwCreateWindow(width, height, name_window, NULL, NULL);
   if (!screen.win)
   {
   printf("Failed to create GLFW window\n");
   return (screen);
   }
   glfwMakeContextCurrent(screen.win);
   glfwSetFramebufferSizeCallback(screen.win, framebuffer_size_callback);
   glViewport(0, 0, width, height);
   return (screen);
   }
   */

Window::Window( std::string title, int width, int height )
{
	_width = width;
	_height = height;

	// EXECPTION ERROR HANDLE
	_win = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);
	if (!_win)
		printf("Failed to create GLFW window\n");
	glfwSetFramebufferSizeCallback(_win, framebuffer_size_callback);
	glViewport(0, 0, _width, _height);

	_mouse = new Mouse(this);
}

Window::~Window( void )
{

}

void Window::makeContextCurrent( void )
{
	glfwMakeContextCurrent(_win);
}

int Window::shouldClose( void )
{
	return(glfwWindowShouldClose(_win));
}
