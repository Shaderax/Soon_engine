#include <GLFW/glfw3.h>

#include "GLFWOpenGLHints.hpp"
#include "Graphics/GLFW/OpenGL/Config.hpp"

namespace Soon
{
	void InitGLFWHints( void )
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}
}
