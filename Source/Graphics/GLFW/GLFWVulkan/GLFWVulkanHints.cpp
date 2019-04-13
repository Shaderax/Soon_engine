#include <GLFW/glfw3.h>

#include "GLFWVulkanHints.hpp"

namespace Soon
{
	void InitGLFWHints( void )
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}
}
