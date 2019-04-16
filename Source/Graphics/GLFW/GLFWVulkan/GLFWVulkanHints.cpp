#include <GLFW/glfw3.h>

#include "GLFWVulkanHints.hpp"

namespace Soon
{
	void InitGLFWHints( void )
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
}
