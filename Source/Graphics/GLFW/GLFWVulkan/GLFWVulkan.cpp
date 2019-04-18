#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
#include "Core/OS/OS.hpp"
#include <iostream>
#include <vector>

namespace Soon
{
	GLFWVulkan::GLFWVulkan( void ) : _physicalDevice(VK_NULL_HANDLE)
	{

	}

	GLFWVulkan::~GLFWVulkan( void )
	{

	}

	int GLFWVulkan::GetQueueFamilyIndex(VkPhysicalDevice device, VkQueueFlagBits queue)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & queue)
				return i;
			i++;
		}
		return (-1);
	}

	bool GLFWVulkan::isDeviceSuitable(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		std::cout << GetQueueFamilyIndex(device, VK_QUEUE_GRAPHICS_BIT) << std::endl;

		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && GetQueueFamilyIndex(device, VK_QUEUE_GRAPHICS_BIT) != -1 /* && deviceFeatures.geometryShader*/;
	}

	void GLFWVulkan::GetPhysicalDeviceInfo( void )
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(_physicalDevice, &deviceProperties);

		std::cout << deviceProperties.deviceName << std::endl; 

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(_physicalDevice, &deviceFeatures);
	}

	void GLFWVulkan::GetPhysicalDeviceInfo( VkPhysicalDevice device )
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		std::cout << deviceProperties.deviceName << std::endl; 

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	}


	void GLFWVulkan::PickPhysicalDevice( void )
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(_vulkanInstance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			std::cout << "failed to find GPUs with Vulkan support!" << std::endl;
			//	throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(_vulkanInstance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (isDeviceSuitable(device))
			{
				_physicalDevice = device;
				break;
			}
		}

		if (_physicalDevice == VK_NULL_HANDLE)
		{
			std::cout << "failed to find a suitable GPU!" << std::endl;
			//			throw std::runtime_error("failed to find a suitable GPU!");
		}

		GetPhysicalDeviceInfo();
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
		//// Check Exten
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		std::cout << "available extensions:" << std::endl;

		for (const auto& extension : extensions)
		{
			std::cout << "\t" << extension.extensionName << std::endl;
		}
		//// end Check Exten

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		VkResult result;
		if ((result = vkCreateInstance(&createInfo, nullptr, &_vulkanInstance)) != VK_SUCCESS) {
			//TODO ERROR
			if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
				printf("Wsh\n");
			printf("IGIGIVIB\n       %d\n", result);
		}
	}

	void GLFWVulkan::CreateLogicalDevice( void )
	{
		int index = GetQueueFamilyIndex(_physicalDevice, VK_QUEUE_GRAPHICS_BIT);

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = index;
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;


		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;

		if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
		{
			std::cout << "failed to create logical device!" << std::endl;
		 //   throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(_device, index, 0, &_graphicsQueue);
	}

	void GLFWVulkan::Initialize( void )
	{
		CreateWindow();
		CreateInstance();
		PickPhysicalDevice();
		CreateLogicalDevice();
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
		vkDestroyDevice(_device, nullptr);
	}
}
