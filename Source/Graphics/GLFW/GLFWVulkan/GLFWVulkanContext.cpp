#include "Core/OS/OS.hpp"
#include "Graphics/GLFW/GLFWCallback.hpp"
#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanContext.hpp"

#include <GLFW/glfw3.h>

namespace Soon
{
	//	void GLFWOpenGLContext::Initialize( void )
	//	{
	//		_context = glfwCreateWindow(width, height, name_window, NULL, NULL);
	//	}
	//
	//
	//	GLFWOpenGLContext* NewContextGL( void )
	//	{
	//		GLFWOpenGLContext* context = new GLFWOpenGLContext;
	//		return (context);
	//	}

	GLFWwindow* NewContextGL( void )
	{
		OS::WindowAttribute winAttr = OS::GetSingleton()->GetWindowAttribute();
		GLFWwindow* context = glfwCreateWindow(winAttr._width, winAttr._height, winAttr._name.c_str(), NULL, NULL);

		uint32_t extensionCount = 0;
	    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//		glfwMakeContextCurrent(context);
		glfwSetFramebufferSizeCallback(context, framebuffer_size_callback);
//		glViewport(0, 0, winAttr._width, winAttr._height);

		return (context);
	}
}
