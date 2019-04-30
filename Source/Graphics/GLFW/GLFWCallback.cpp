#include "GLFWCallback.hpp"
#include <iostream>

namespace Soon
{
	void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
//		auto app = reinterpret_cast<GLFWVulkan*>(glfwGetWindowUserPointer(window));
//		app->framebufferResized = true;
//		(void)window;
//		glViewport(0, 0, width, height);
	}

	void error_callback(int error, const char* description)
	{
		std::cerr << "Error: " << description << std::endl;
	}
}
