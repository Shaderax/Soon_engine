#ifndef WINDOW_HPP
# define WINDOW_HPP

#include "scop.h"
class Mouse;

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
		int shouldClose( void );
};


#endif
