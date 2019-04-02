#pragma once

#include "Mouse.hpp"
#include <iostream>
#include <string>

class Mouse;

namespace Soon
{
	class GLFWWindow
	{
		public:
			int			_width;
			int			_height;
			GLFWwindow*	_win;
//			Mouse*		_mouse;

			GLFWWindow( std::string title, int width = 1280, int height = 720 );
			~GLFWWindow( void );

			void MakeContextCurrent( void );
			bool ShouldClose( void );
	};
}

void	framebuffer_size_callback(GLFWwindow *window, int width, int height);
