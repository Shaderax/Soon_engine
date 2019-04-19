#pragma once

#include <GLFW/glfw3.h>

namespace Soon
{
	void	framebuffer_size_callback(GLFWwindow *window, int width, int height);

	void error_callback(int error, const char* description);
}
