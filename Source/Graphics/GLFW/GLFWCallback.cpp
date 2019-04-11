#include "GLFWCallback.hpp"

namespace Soon
{
	void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		(void)window;
		glViewport(0, 0, width, height);
	}
}
