#include "Soon.hpp"
#include "Init.hpp"
#include "Error.hpp"
#include <stdio.h>

namespace Soon
{
	bool	InitGlfw( void )
	{
		if (!glfwInit())
		{
			printf("%s", "Failed to initialize GLFW\n");
			return (false);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
# if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
# endif
		return (true);
	}

	bool Init( void )
	{
		if (!InitGlfw())
			return (Soon::error("Error : glfw init"));
		return (true);
	}
}

