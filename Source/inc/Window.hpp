#pragma once

#include "Soon.hpp"
#include "Mouse.hpp"
#include <iostream>
#include <string>

class Mouse;

namespace Soon
{
	class Window
	{
		public:
			int			_width;
			int			_height;
			Mouse*		_mouse;
			GLFWwindow*	_win;

			Window( std::string title, int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT );
			~Window( void );

			void makeContextCurrent( void );
			bool shouldClose( void );
	};
}

void	framebuffer_size_callback(GLFWwindow *window, int width, int height);
