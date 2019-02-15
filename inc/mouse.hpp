#pragma once

#include "Window.hpp"

namespace  Soon { class Window; };

class Mouse
{
	public :
		float   _last_x;
		float   _last_y;
		double  _new_x;
		double  _new_y;
		float   _off_x;
		float   _off_y;
		float   _sensitivity;
		float   _yaw;
		float   _pitch;

		Mouse( Soon::Window *window );
		~Mouse( void );

		bool mouseMoved( void );
};
