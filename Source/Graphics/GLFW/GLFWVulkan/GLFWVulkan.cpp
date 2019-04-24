#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
#include "Core/OS/OS.hpp"
#include <iostream>
#include <vector>
#include <map>
#include "Core/Error.hpp"
#include "GLFW/glfw3.h"
#include <set>
#include <algorithm>
#include "string.h"
//#include <MoltenVK/vk_mvk_moltenvk.h>

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


#define NDEBUG 1
//#ifdef NDEBUG
//const bool enableValidationLayers = false;
//#else
const bool enableValidationLayers = true;
//#endif

bool checkValidationLayerSupport( void ) {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	std::cout << "availableLayers : " << layerCount << std::endl;
	for (const auto& layerProperties : availableLayers)
	{
		std::cout << "\t" << layerProperties.layerName << std::endl;
	}

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}

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
		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		if (GetQueueFamilyIndex(device, VK_QUEUE_GRAPHICS_BIT) == -1 || !extensionsSupported || !swapChainAdequate)
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
		if (enableValidationLayers && !checkValidationLayerSupport())
			throw std::runtime_error("validation layers requested, but not available!");

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

		std::cout << "AVAILABLE EXTENSIONS : " << extensionCount << std::endl;
		std::vector<char const *> extNames(extensionCount);
		for (uint32_t i = 0; i < extensionCount; ++i)
		{
			extNames[i] = extensions[i].extensionName;
			std::cout << "\t" << extNames[i] << std::endl;
		}
		//// end Check Exten

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::cout << "GLFW - EXTENSIONS : " << glfwExtensionCount << std::endl;
		for (size_t i = 0; i < glfwExtensionCount; ++i) {
			std::cout << "\t" << glfwExtensions[i] << std::endl;
		}

		std::vector<const char*> vecExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers)
			vecExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		createInfo.enabledExtensionCount = static_cast<uint32_t>(vecExtensions.size());
		createInfo.ppEnabledExtensionNames = vecExtensions.data();

		std::vector<const char*> ok;

		ok.push_back("VK_LAYER_LUNARG_standard_validation");
		if (enableValidationLayers)
		{
			for (const char* kk : ok)
				std::cout << kk << std::endl;
			createInfo.enabledLayerCount = 1;//static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = &ok.data()[0];//validationLayers.data();
		}
		else
			createInfo.enabledLayerCount = 0;

		VkResult result;
		if ((result = vkCreateInstance(&createInfo, nullptr, &_vulkanInstance)) != VK_SUCCESS)
			SOON_ERR_THROW(0, "Can't Initialize a Vulkan Instance");
	}

	void GLFWVulkan::CreateLogicalDevice( void )
	{
		std::cout << "VROUM VROUM : " << VK_KHR_SWAPCHAIN_EXTENSION_NAME << std::endl;
		// TODO //Get queue for drawing and queue for presentation
		int index = GetQueueFamilyIndex(_physicalDevice, VK_QUEUE_GRAPHICS_BIT);

		//		std::cout << index << std::endl;
		//		SOON_ERR_THROW((index != -1), "Did not find FamilyIndex");

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
		createInfo.enabledExtensionCount = 1;//static_cast<uint32_t>(deviceExtensions.size());
		std::vector<const char*> ko;
		ko.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		createInfo.ppEnabledExtensionNames = &ko.data()[0];//deviceExtensions.data();
		std::cout << "COUCOUC : " << deviceExtensions.size() << std::endl;

		if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
			SOON_ERR_THROW(0, "failed to create logical device!");

		vkGetDeviceQueue(_device, index, 0, &_graphicsQueue);
		vkGetDeviceQueue(_device, index, 0, &_presentQueue);
	}

	void GLFWVulkan::CreateSurface( void )
	{
		VkResult ret;
		if ((ret = glfwCreateWindowSurface(_vulkanInstance, _window, nullptr, &_surface)) != VK_SUCCESS)
			SOON_ERR_THROW(0, "failed to create window surface!");
	}

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
			return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};

		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		}

		return availableFormats[0];
	}

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				std::cout << "VK_PRESENT_MODE_MAILBOX_KHR" << std::endl;
				return availablePresentMode;
			}
			else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			{
				std::cout << "VK_PRESENT_MODE_IMMEDIATE_KHR" << std::endl;
				bestMode = availablePresentMode;
			}
		}

		std::cout << "VK_PRESENT_MODE_LIFO_KHR" << std::endl;
		return bestMode;
	}

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		OS::WindowAttribute winAttr = OS::GetSingleton()->GetWindowAttribute();

		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			VkExtent2D actualExtent = {winAttr._width, winAttr._height};

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}
	
	//SWAP CHAIN
	SwapChainSupportDetails GLFWVulkan::QuerySwapChainSupport(VkPhysicalDevice device)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	void GLFWVulkan::CreateSwapChain( void )
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		std::cout << surfaceFormat.format << std::endl;
		std::cout << surfaceFormat.colorSpace << std::endl;
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
		std::cout << presentMode << std::endl;
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);
		std::cout << extent.width << std::endl;
		std::cout << extent.height << std::endl;

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
			imageCount = swapChainSupport.capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _surface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapChain) != VK_SUCCESS)
			SOON_ERR_THROW(0, "Cant Create SwapChain");

		vkGetSwapchainImagesKHR(_device, _swapChain, &imageCount, nullptr);
		_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(_device, _swapChain, &imageCount, _swapChainImages.data());

		_swapChainImageFormat = surfaceFormat.format;
		_swapChainExtent = extent;
	}

	void GLFWVulkan::SetupDebugMessenger( void )
	{
		if (!enableValidationLayers) return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;

		if (CreateDebugUtilsMessengerEXT(_vulkanInstance, &createInfo, nullptr, &_debugMessenger) != VK_SUCCESS)
			throw std::runtime_error("failed to set up debug messenger!");
	}

	void GLFWVulkan::Initialize( void )
	{
		if (!glfwVulkanSupported())
			std::cout << "VULKAN Y VEUT PAS SANS DOUTE A CAUSE DE SE MOLTENVK DE MERDE" << std::endl;
		CreateWindow();
		CreateInstance();
		SetupDebugMessenger();
		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain();
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
		if (enableValidationLayers)
			DestroyDebugUtilsMessengerEXT(_vulkanInstance, _debugMessenger, nullptr);
		glfwDestroyWindow(_window);
		vkDestroySurfaceKHR(_vulkanInstance, _surface, nullptr);
		vkDestroyDevice(_device, nullptr);
		vkDestroyInstance(_vulkanInstance, nullptr);
		vkDestroySwapchainKHR(_device, _swapChain, nullptr);
	}
}
