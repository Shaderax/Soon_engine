#include "GLFWInput.hpp"
#include "Core/OS/OS.hpp"

#include "GLFW/glfw3.h"

namespace Soon
{
	GLFWInput::GLFWInput( void )
	{

	}

	bool GLFWInput::GetKeyDown( int key )
	{
		return (glfwGetKey(static_cast<GLFWwindow*>(OS::GetSingleton()->GetContext()), key) == GLFW_PRESS);
	}
}
