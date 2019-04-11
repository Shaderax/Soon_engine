#include "InitGLFW.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

namespace
{
	bool InitGLFW( void )
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return (false);
		}
		return (true);
	}
}
