#include "Init.hpp"
#include "Callback.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Core/Error.hpp"

namespace Soon
{
	bool InitGLFW( void )
	{
		glfwSetErrorCallback(error_callback);
		if (!glfwInit())
		{
			SOON_ERR_THROW(0, "Failed to initialize GLFW");
			return (false);
		}
		return (true);
	}
}
