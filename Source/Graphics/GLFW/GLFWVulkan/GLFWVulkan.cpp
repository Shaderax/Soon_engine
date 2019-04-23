#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
#include "Core/OS/OS.hpp"
#include <iostream>
#include <vector>
#include <map>
#include "Core/Error.hpp"
#include "GLFW/glfw3.h"
#include <set>
//#include <MoltenVK/vk_mvk_moltenvk.h>


namespace Soon
{
	GLFWVulkan::GLFWVulkan( void ) : _physicalDevice(VK_NULL_HANDLE)
	{

	}

	GLFWVulkan::~GLFWVulkan( void )
	{

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
	
	int GLFWVulkan::GetQueueFamilyIndex(VkPhysicalDevice device, VkQueueFlagBits queue)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);

			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & queue && presentSupport)
				return i;

			i++;
		}
		return (-1);
	}

	const std::vector<const char*> deviceExtensions =
	{
		    VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device)
	{
	    uint32_t extensionCount;
	    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	    for (const auto& extension : availableExtensions)
		        requiredExtensions.erase(extension.extensionName);

	    return requiredExtensions.empty();	
	}

	int GLFWVulkan::RateDeviceSuitable(VkPhysicalDevice device)
	{
		int score = 0;

		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		bool extensionsSupported = CheckDeviceExtensionSupport(device);
		if (GetQueueFamilyIndex(device, VK_QUEUE_GRAPHICS_BIT) == -1 || !extensionsSupported)
			return (score);
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 10;
		return score + 1;
	}

	void GLFWVulkan::PickPhysicalDevice( void )
	{
		std::map<int, VkPhysicalDevice> scoreDevice;

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(_vulkanInstance, &deviceCount, nullptr);

		if (deviceCount == 0)
			SOON_ERR_THROW(0, "failed to find GPUs with Vulkan support!");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(_vulkanInstance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			int score = 0;

			score = RateDeviceSuitable(device);
			scoreDevice.insert(std::make_pair(score, device));
		}

		if (scoreDevice.rbegin()->first > 0)
			_physicalDevice = scoreDevice.rbegin()->second;
		else
			SOON_ERR_THROW(0, "failed to find a suitable GPU!");

		if (_physicalDevice == VK_NULL_HANDLE)
			SOON_ERR_THROW(0, "failed to find a suitable GPU!");

		GetPhysicalDeviceInfo();
	}

	void GLFWVulkan::CreateWindow( void )
	{
		OS::WindowAttribute winAttr = OS::GetSingleton()->GetWindowAttribute();
		_window = glfwCreateWindow(winAttr._width, winAttr._height, winAttr._name.c_str()  , NULL, NULL);
		SOON_ERR_THROW(_window, "Can't Initialize Window");
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

		std::cout << "AVAILABLE EXT\n";
		std::vector<char const *> extNames(extensionCount);
		for (uint32_t i = 0; i < extensionCount; ++i)
		{
			extNames[i] = extensions[i].extensionName;
			std::cout << extNames[i] << std::endl;
		}
		//// end Check Exten

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::cout << "GLFW EXT : " << glfwExtensionCount << std::endl;
		for (size_t i = 0; i < glfwExtensionCount; ++i) {
			std::cout << glfwExtensions[i] << std::endl;
		}


		/*std::cout << "GLFW - EXTENSIONS\n";
		for (const auto &ext: glfwExtensions) {
			std::cout << ext.extensionName << std::endl;
		}*/

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		//createInfo.enabledExtensionCount = extNames.size();
		//createInfo.ppEnabledExtensionNames = extNames.data();

		createInfo.enabledLayerCount = 0;

		VkResult result;
		if ((result = vkCreateInstance(&createInfo, nullptr, &_vulkanInstance)) != VK_SUCCESS)
		{
			SOON_ERR_THROW(0, "Can't Initialize a Vulkan Instance");
		}
	}

	void GLFWVulkan::CreateLogicalDevice( void )
	{
		// TODO //Get queue for drawing and queue for presentation
		int index = GetQueueFamilyIndex(_physicalDevice, VK_QUEUE_GRAPHICS_BIT);

		SOON_ERR_THROW((index == 0), "Did not find FamilyIndex");

		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = index;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
			SOON_ERR_THROW(0, "failed to create logical device!");

		vkGetDeviceQueue(_device, index, 0, &_graphicsQueue);
	}

	void GLFWVulkan::CreateSurface( void )
	{
		VkResult ret;
		if ((ret = glfwCreateWindowSurface(_vulkanInstance, _window, nullptr, &_surface)) != VK_SUCCESS)
		{
			if (ret == GLFW_NOT_INITIALIZED)
				std::cout << " GLFW_NOT_INITIALIZED" << std::endl;
			else if (ret == GLFW_API_UNAVAILABLE)
				std::cout << "GLFW_API_UNAVAILABLE" << std::endl;
			else if (ret == GLFW_PLATFORM_ERROR)
				std::cout << "GLFW_PLATFORM_ERROR" << std::endl;
			else if (ret == GLFW_INVALID_VALUE)
				std::cout << "GLFW_INVALID_VALUE" << std::endl;
			else if (ret == VK_ERROR_INITIALIZATION_FAILED)
				std::cout << "VK_ERROR_INITIALIZATION_FAILED" << std::endl;
			else if (ret == VK_ERROR_EXTENSION_NOT_PRESENT)
				std::cout << "VK_ERROR_EXTENSION_NOT_PRESENT" << std::endl;
			SOON_ERR_THROW(0, "failed to create window surface!");
		}
	}

	void GLFWVulkan::Initialize( void )
	{
		if (!glfwVulkanSupported())
		{
			std::cout << "VULKAN Y VEUT PAS SANS DOUTE A CAUSE DE SE MOLTENVK DE MERDE" << std::endl;
			    // Vulkan is available, at least for compute
		}
		CreateWindow();
		CreateInstance();
		CreateSurface();
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
		vkDestroySurfaceKHR(_vulkanInstance, _surface, nullptr);
		vkDestroyDevice(_device, nullptr);
		vkDestroyInstance(_vulkanInstance, nullptr);
	}
}
