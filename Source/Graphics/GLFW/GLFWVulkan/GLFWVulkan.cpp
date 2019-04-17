#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
#include "Core/OS/OS.hpp"

namespace Soon
{
	GLFWVulkan::GLFWVulkan( void )
	{

	}

	GLFWVulkan::~GLFWVulkan( void )
	{

	}

	void GLFWVulkan::CreateWindow( void )
	{
		OS::WindowAttribute winAttr = OS::GetSingleton()->GetWindowAttribute();
		_window = glfwCreateWindow(winAttr._width, winAttr._height, winAttr._name.c_str()  , NULL, NULL);
	}

	void GLFWVulkan::CreateInstance( void )
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = nullptr;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Soon Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &_vulkanInstance);

		VkResult ret;
		if ((ret = vkCreateInstance(&createInfo, nullptr, &_vulkanInstance)) != VK_SUCCESS) {
			//TODO ERROR
			if (ret == VK_ERROR_INCOMPATIBLE_DRIVER)
				printf("Wsh\n");
			printf("IGIGIVIB\n       %d\n", ret);
		}
	}

	void GLFWVulkan::Initialize( void )
	{
		CreateWindow();
		CreateInstance();
	}

	void* GLFWVulkan::GetContext( void )
	{
		return (_window);
	}

	void NewGraphicsInstance( void )
	{
		GLFWVulkan* instance = new GLFWVulkan;
	}

	void GLFWVulkan::Destroy( void )
	{
		glfwDestroyWindow(_window);
	}
}
