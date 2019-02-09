#ifndef MOUSE_HPP
# define MOUSE_HPP

#include "scop.h"
class Window;

class Mouse
{
	public :
		float   last_x;
		float   last_y;
		double  new_x;
		double  new_y;
		float   off_x;
		float   off_y;
		float   sensitivity;
		float   yaw;
		float   pitch;

		Mouse( Window *window );
		~Mouse( void );

		int mouseMoved( void );
};


#endif
