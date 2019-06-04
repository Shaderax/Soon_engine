#include "Input.hpp"
#include "Core/OS/OS.hpp"
#include "GLFW/glfw3.h"

namespace Soon
{
//	Input *Input::_singleton = nullptr;

//	Input* Input::GetSingleton( void )
//	{
//		return (_singleton);
//	}

	Input::Input( void )
	{
//		_singleton = this;
	}

	bool Input::GetKeyDown( int key )
	{
		return (glfwGetKey(OS::GetInstance()->GetWindow(), key) == GLFW_PRESS);
	}
}
