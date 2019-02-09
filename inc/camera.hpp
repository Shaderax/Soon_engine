#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "scop.h"

class Camera
{
	public :
		t_vec4  pos;
		t_vec4  target;
		t_vec4  rotate;
		t_mat4  view;
		t_mat4  proj;
		float   near;
		float   far;
		float   speed;

		Camera( void );
		~Camera( void );
}

#endif
