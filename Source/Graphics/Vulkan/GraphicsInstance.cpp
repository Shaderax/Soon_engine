#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Core/OS/OS.hpp"
#include "Core/Error.hpp"
#include "GLFW/glfw3.h"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>
#include <string.h>
#include <string>
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/Common/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "GraphicsPipelineConf.hpp"

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

bool checkValidationLayerSupport( void )
{
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
	GraphicsInstance* GraphicsInstance::_singleton = nullptr;

	GraphicsInstance* GraphicsInstance::GetInstance( void )
	{
		return (_singleton);
	}

	GraphicsInstance::GraphicsInstance( void ) : _physicalDevice(VK_NULL_HANDLE), _currentFrame(0), _framebufferResized(false)
	{
		_singleton = this;
	}

	GraphicsInstance::~GraphicsInstance( void )
	{

	}

	void GraphicsInstance::GetPhysicalDeviceInfo( void )
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(_physicalDevice, &deviceProperties);

		std::cout << deviceProperties.deviceName << std::endl; 

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(_physicalDevice, &deviceFeatures);
	}

	void GraphicsInstance::GetPhysicalDeviceInfo( VkPhysicalDevice device )
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		std::cout << deviceProperties.deviceName << std::endl; 

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	}

	int GraphicsInstance::GetQueueFamilyIndex(VkPhysicalDevice device, VkQueueFlagBits queue)
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

	int GraphicsInstance::RateDeviceSuitable(VkPhysicalDevice device)
	{
		int score = 0;

		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);


		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

		bool extensionsSupported = CheckDeviceExtensionSupport(device);
		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		if (GetQueueFamilyIndex(device, VK_QUEUE_GRAPHICS_BIT) == -1 || !extensionsSupported || !swapChainAdequate/* || supportedFeatures.samplerAnisotropy*/)
			return (score);
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 10;
		return score + 1;
	}

	void GraphicsInstance::PickPhysicalDevice( void )
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

	void GraphicsInstance::CreateWindow( void )
	{
		OS::WindowAttribute winAttr = OS::GetInstance()->GetWindowAttribute();
		_window = glfwCreateWindow(winAttr._width, winAttr._height, winAttr._name.c_str()  , NULL, NULL);
		glfwSetWindowUserPointer(_window, this);
		glfwSetFramebufferSizeCallback(_window, FramebufferResizeCallback);
		SOON_ERR_THROW(_window, "Can't Initialize Window");
	}

	void GraphicsInstance::CreateInstance( void )
	{
		//		if (enableValidationLayers && !checkValidationLayerSupport())
		//			throw std::runtime_error("validation layers requested, but not available!");

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

	void GraphicsInstance::CreateLogicalDevice( void )
	{
		std::cout << "VK_KHR_SWAPCHAIN_EXTENSION_NAME : " << VK_KHR_SWAPCHAIN_EXTENSION_NAME << std::endl;
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
		deviceFeatures.samplerAnisotropy = VK_TRUE;

		//TODO
		deviceFeatures.fillModeNonSolid = true;

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 1;//static_cast<uint32_t>(deviceExtensions.size());
		std::vector<const char*> ko;
		ko.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		createInfo.ppEnabledExtensionNames = &ko.data()[0];//deviceExtensions.data();

		if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
			SOON_ERR_THROW(0, "failed to create logical device!");

		vkGetDeviceQueue(_device, index, 0, &_graphicsQueue);
		vkGetDeviceQueue(_device, index, 0, &_presentQueue);
	}

	void GraphicsInstance::CreateSurface( void )
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

		std::cout << "VK_PRESENT_MODE_FIFO_KHR" << std::endl;
		return bestMode;
	}

	VkExtent2D GraphicsInstance::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		OS::WindowAttribute winAttr = OS::GetInstance()->GetWindowAttribute();

		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			int width, height;
			glfwGetFramebufferSize(_window, &width, &height);
			VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
			//VkExtent2D actualExtent = {winAttr._width, winAttr._height};

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	//SWAP CHAIN
	SwapChainSupportDetails GraphicsInstance::QuerySwapChainSupport(VkPhysicalDevice device)
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

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	void GraphicsInstance::CreateSwapChain( void )
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		//		std::cout << "Surface Format" << surfaceFormat.format << std::endl;
		//		std::cout << "Surface Color space : " << surfaceFormat.colorSpace << std::endl;
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
		//		std::cout << "Present Mode : " << presentMode << std::endl;
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);
		std::cout << "Extent Width : " << extent.width << std::endl;
		std::cout <<  "Extent Height : " << extent.height << std::endl;

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

	void GraphicsInstance::SetupDebugMessenger( void )
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

	void GraphicsInstance::CreateImageViews( void )
	{
		_swapChainImageViews.resize(_swapChainImages.size());

		for (size_t i = 0; i < _swapChainImages.size(); i++)
			_swapChainImageViews[i] = CreateImageView(_swapChainImages[i], _swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_VIEW_TYPE_2D);
	}

	VkImageView GraphicsInstance::CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageViewType viewType)
	{
		VkImageViewCreateInfo viewInfo = {};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = image;
		viewInfo.viewType = viewType;//VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = format;
		//		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		if (viewType == VK_IMAGE_VIEW_TYPE_2D)
		{
			viewInfo.subresourceRange.layerCount = 1;
		}
		else if (viewType == VK_IMAGE_VIEW_TYPE_CUBE)
		{
			viewInfo.subresourceRange.layerCount = 6;
		}
		viewInfo.subresourceRange.aspectMask = aspectFlags;

		VkImageView imageView;
		if (vkCreateImageView(_device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
			throw std::runtime_error("failed to create texture image view!");

		return imageView;
	}

	static std::vector<char> readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("failed to open file!" + filename);
		}

		size_t fileSize = (size_t) file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	VkShaderModule GraphicsInstance::CreateShaderModule(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;

		if (vkCreateShaderModule(_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
			throw std::runtime_error("failed to create shader module!");
    
		return shaderModule;
	}

	VkPipeline GraphicsInstance::CreateGraphicsPipeline(
			GraphicsPipelineConf&								conf,
			std::string 									pathVert,
			std::string										pathFrag)
	{
		VkPipeline                      graphicsPipeline;

		auto vertShaderCode = readFile(pathVert);
		auto fragShaderCode = readFile(pathFrag);

		VkShaderModule vertShaderModule = CreateShaderModule(vertShaderCode);
		VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

		conf.pipelineInfo.stageCount = 2;

		//
		/*
		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

		if (sType == GraphicsInstance::ShaderType::VERTEX_FRAGMENT)
			inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		else
			inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport = {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float) _swapChainExtent.width;
		viewport.height = (float) _swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor = {};
		scissor.offset = {0, 0};
		scissor.extent = _swapChainExtent;

		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;

		if (sType == GraphicsInstance::ShaderType::VERTEX_FRAGMENT)
			rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		else
			rasterizer.polygonMode = VK_POLYGON_MODE_POINT;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;// VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		//		depthStencil.minDepthBounds = 0.0f; // Optional
		//		depthStencil.maxDepthBounds = 1.0f; // Optional
		depthStencil.stencilTestEnable = VK_FALSE;
		//		depthStencil.front = {}; // Optional
		//		depthStencil.back = {}; // Optional

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		/////////// PIPELINE LAYOUT ////////////

		VkGraphicsPipelineCreateInfo pipelineInfo = {};
*/
	//	conf.pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		conf.pipelineInfo.stageCount = 2;
		conf.pipelineInfo.pStages = shaderStages;
	//	conf.pipelineInfo.pVertexInputState = &vertexInputInfo;
	//	conf.pipelineInfo.pInputAssemblyState = &inputAssembly;
	//	conf.pipelineInfo.pViewportState = &viewportState;
	//	conf.pipelineInfo.pRasterizationState = &rasterizer;
	//	conf.pipelineInfo.pMultisampleState = &multisampling;
	//	conf.pipelineInfo.pColorBlendState = &colorBlending;
	//	conf.pipelineInfo.pDepthStencilState = &depthStencil;
	//	conf.pipelineInfo.layout = pipelineLayout;
	//	conf.pipelineInfo.renderPass = _renderPass;
	//	conf.pipelineInfo.subpass = 0;
	//	conf.pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &conf.pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
			throw std::runtime_error("failed to create graphics pipeline!");

		vkDestroyShaderModule(_device, fragShaderModule, nullptr);
		vkDestroyShaderModule(_device, vertShaderModule, nullptr);

		return (graphicsPipeline);
	}

	VkPipeline GraphicsInstance::CreateComputePipeline(
			VkPipelineLayout						pipelineLayout,
			std::string 							pathCompute)
	{
		VkPipeline                      computePipeline;

		auto computeShaderCode = readFile(pathCompute);

		VkShaderModule computeShaderModule = CreateShaderModule(computeShaderCode);

		VkPipelineShaderStageCreateInfo computeShaderStageInfo = {};
		computeShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		computeShaderStageInfo.module = computeShaderModule;
		computeShaderStageInfo.pName = "main";

//		VkPipelineShaderStageCreateInfo shaderStages[] = {computeShaderStageInfo};

		VkComputePipelineCreateInfo	computePipelineInfos = {};
		computePipelineInfos.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		computePipelineInfos.stage = computeShaderStageInfo;
		computePipelineInfos.layout = pipelineLayout;

		if (vkCreateComputePipelines(_device, VK_NULL_HANDLE, 1, &computePipelineInfos, nullptr, &computePipeline) != VK_SUCCESS)
			throw std::runtime_error("failed to create graphics pipeline!");

		vkDestroyShaderModule(_device, computeShaderModule, nullptr);

		return (computePipeline);
	}

	VkPipelineLayout GraphicsInstance::CreatePipelineLayout( std::vector<VkDescriptorSetLayout> descriptorSetLayout )
	{
		VkPipelineLayout pipelineLayout;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = descriptorSetLayout.size();
		pipelineLayoutInfo.pSetLayouts = (descriptorSetLayout.data());
		//		pipelineLayoutInfo.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(_device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline layout!");

		return pipelineLayout;
	}

	void GraphicsInstance::CreateRenderPass( void )
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = _swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentDescription depthAttachment = {};
		depthAttachment.format = FindDepthFormat();
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthAttachmentRef = {};
		depthAttachmentRef.attachment = 1;
		depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
		VkRenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS)
			throw std::runtime_error("failed to create render pass!");
		std::cout << "Created render pass" << std::endl;
	}

	void GraphicsInstance::CreateFramebuffers( void )
	{
		_swapChainFramebuffers.resize(_swapChainImageViews.size());

		for (size_t i = 0; i < _swapChainImageViews.size(); i++)
		{
			std::array<VkImageView, 2>	attachments; 
			attachments[0] = _swapChainImageViews[i],
			attachments[1] = _depthImageView;

			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = _renderPass;
			framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = _swapChainExtent.width;
			framebufferInfo.height = _swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(_device, &framebufferInfo, nullptr, &_swapChainFramebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void GraphicsInstance::CreateCommandPool( void )
	{
		int index = GetQueueFamilyIndex(_physicalDevice, VK_QUEUE_GRAPHICS_BIT);

		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = index;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		if (vkCreateCommandPool(_device, &poolInfo, nullptr, &_commandPool) != VK_SUCCESS)
			throw std::runtime_error("failed to create command pool!");
	}

	void GraphicsInstance::CreateCommandBuffers( void )
	{
		_commandBuffers.resize(_swapChainFramebuffers.size());

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = _commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t) _commandBuffers.size();

		if (vkAllocateCommandBuffers(_device, &allocInfo, _commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");

		for (size_t i = 0; i < _commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			//
			if (vkBeginCommandBuffer(_commandBuffers[i], &beginInfo) != VK_SUCCESS)
				throw std::runtime_error("failed to begin recording command buffer!");

			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = _renderPass;
			renderPassInfo.framebuffer = _swapChainFramebuffers[i];
			renderPassInfo.renderArea.offset = {0, 0};
			renderPassInfo.renderArea.extent = _swapChainExtent;

			std::array<VkClearValue, 2> clearValues = {};
			clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
			clearValues[1].depthStencil = {1.0f, 0};
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
      
			vkCmdEndRenderPass(_commandBuffers[i]);
			if (vkEndCommandBuffer(_commandBuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to record command buffer!");
		}
	}

	void GraphicsInstance::FillCommandBuffer( void )
	{
		for (size_t i = 0; i < _commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			if (vkBeginCommandBuffer(_commandBuffers[i], &beginInfo) != VK_SUCCESS)
				throw std::runtime_error("failed to begin recording command buffer!");

			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = _renderPass;
			renderPassInfo.framebuffer = _swapChainFramebuffers[i];
			renderPassInfo.renderArea.offset = {0, 0};
			renderPassInfo.renderArea.extent = _swapChainExtent;

			std::array<VkClearValue, 2> clearValues = {};
			clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
			clearValues[1].depthStencil = {1.0f, 0};
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			GraphicsRenderer::GetInstance()->GraphicPipelinesBindCaller(_commandBuffers[i], i);

			vkCmdEndRenderPass(_commandBuffers[i]);

			GraphicsRenderer::GetInstance()->ComputePipelinesBindCaller(_commandBuffers[i], i);

			if (vkEndCommandBuffer(_commandBuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to record command buffer!");
		}
	}

#define MAX_FRAMES_IN_FLIGHT 2

	void GraphicsInstance::CreateSyncObjects( void )
	{
		_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			if (vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != VK_SUCCESS ||
					vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != VK_SUCCESS ||
					vkCreateFence(_device, &fenceInfo, nullptr, &_inFlightFences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void GraphicsInstance::DrawFrame( void )
	{
		vkWaitForFences(_device, 1, &_inFlightFences[_currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(_device, _swapChain, std::numeric_limits<uint64_t>::max(), _imageAvailableSemaphores[_currentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to acquire swap chain image!");

		GraphicsRenderer::GetInstance()->UpdateAllDatas(imageIndex);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = {_imageAvailableSemaphores[_currentFrame]};
		VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_commandBuffers[imageIndex];

		VkSemaphore signalSemaphores[] = {_renderFinishedSemaphores[_currentFrame]};
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(_device, 1, &_inFlightFences[_currentFrame]);

		if (vkQueueSubmit(_graphicsQueue, 1, &submitInfo, _inFlightFences[_currentFrame]) != VK_SUCCESS)
			throw std::runtime_error("failed to submit draw command buffer!");

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = {_swapChain};
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(_presentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _framebufferResized)
		{
			_framebufferResized = false;
			RecreateSwapChain();
		}
		else if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chain image!");

		_currentFrame = (_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void GraphicsInstance::RecreateSwapChain( void )
	{
		int width = 0, height = 0;
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(_window, &width, &height);
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(_device);

		CleanupSwapChain();

		CreateSwapChain();
		CreateImageViews();
		CreateRenderPass();

		CreateDepthResources();
		CreateFramebuffers();
		CreateDescriptorPool();
		CreateCommandBuffers();

		GraphicsRenderer::GetInstance()->RecreateAllPipelines();
		GraphicsRenderer::GetInstance()->RecreateAllUniforms();
		FillCommandBuffer();
	}

	void GraphicsInstance::CleanupSwapChain( void )
	{
		vkDestroyImageView(_device, _depthImageView, nullptr);
		vkDestroyImage(_device, _depthImage, nullptr);
		vkFreeMemory(_device, _depthImageMemory, nullptr);

		for (auto framebuffer : _swapChainFramebuffers)
			vkDestroyFramebuffer(_device, framebuffer, nullptr);

		vkFreeCommandBuffers(_device, _commandPool, static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());

		// TODO
		// GraphicsRenderer::GetInstance()->DestroyAllGraphicsPipeline();
//		vkDestroyPipeline(_device, _graphicsPipeline, nullptr);
//		vkDestroyPipelineLayout(_device, _pipelineLayout, nullptr);

		vkDestroyRenderPass(_device, _renderPass, nullptr);

		for (auto imageView : _swapChainImageViews) {
			vkDestroyImageView(_device, imageView, nullptr);
		}

		vkDestroySwapchainKHR(_device, _swapChain, nullptr);

		// TODO
		// GraphicsRenderer::GetInstance()->DestroyAllUniforms();
		// Uniforms
//		int j = -1;
//		while (++j < GraphicsRenderer::GetInstance()->GetvkBuffers().size())
//		{
//			for (size_t i = 0; i < _swapChainImages.size(); i++)
//			{
//				vkDestroyBuffer(_device, GraphicsRenderer::GetInstance()->GetUniformBuffers().at(j)._Buffer[i], nullptr);
//				vkFreeMemory(_device, GraphicsRenderer::GetInstance()->GetUniformBuffers().at(j)._BufferMemory[i], nullptr);
//			}
//		}

		vkDestroyDescriptorPool(_device, _descriptorPool, nullptr);
	}

	uint32_t GraphicsInstance::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;
		}

		throw std::runtime_error("failed to find suitable memory type!");
	}
	
	std::vector<BufferRenderer> GraphicsInstance::CreateStorageBuffer( uint32_t size, void* ptrData )
	{
		std::vector<BufferRenderer>					bufRenderer;
		std::cout << "Vertex BUFFER CREATION : " << size << std::endl;

		bufRenderer.resize(2);

		bufRenderer[0]._Buffer.resize(1);
		bufRenderer[0]._BufferMemory.resize(1);
		bufRenderer[1]._Buffer.resize(1);
		bufRenderer[1]._BufferMemory.resize(1);

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, bufRenderer[0]._Buffer[0], bufRenderer[0]._BufferMemory[0]);

		if (ptrData)
		{
			void* data;
			vkMapMemory(_device, bufRenderer[0]._BufferMemory[0], 0, size, 0, &data);
			memcpy(data, ptrData, (size_t)size);
			vkUnmapMemory(_device, bufRenderer[0]._BufferMemory[0]);
		}

		CreateBuffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufRenderer[1]._Buffer[0], bufRenderer[1]._BufferMemory[0] );

		CopyBuffer(bufRenderer[0]._Buffer[0], bufRenderer[1]._Buffer[0], size);

		//		vkDestroyBuffer(_device, stagingBuffer, nullptr);
		//		vkFreeMemory(_device, stagingBufferMemory, nullptr);

		return ( bufRenderer );
	}

	std::vector<BufferRenderer> GraphicsInstance::CreateVertexBuffer( uint32_t size, void* ptrData )
	{
		std::vector<BufferRenderer>					bufRenderer;
		std::cout << "Vertex BUFFER CREATION : " << size << std::endl;

		bufRenderer.resize(2);

		bufRenderer[0]._Buffer.resize(1);
		bufRenderer[0]._BufferMemory.resize(1);
		bufRenderer[1]._Buffer.resize(1);
		bufRenderer[1]._BufferMemory.resize(1);

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, bufRenderer[0]._Buffer[0], bufRenderer[0]._BufferMemory[0]);

		if (ptrData)
		{
			void* data;
			vkMapMemory(_device, bufRenderer[0]._BufferMemory[0], 0, size, 0, &data);
			memcpy(data, ptrData, (size_t)size);
			vkUnmapMemory(_device, bufRenderer[0]._BufferMemory[0]);
		}

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufRenderer[1]._Buffer[0], bufRenderer[1]._BufferMemory[0] );

		CopyBuffer(bufRenderer[0]._Buffer[0], bufRenderer[1]._Buffer[0], size);

		//		vkDestroyBuffer(_device, stagingBuffer, nullptr);
		//		vkFreeMemory(_device, stagingBufferMemory, nullptr);

		return ( bufRenderer );
	}

	GLFWwindow* GraphicsInstance::GetWindow( void )
	{
		return (_window);
	}

	void NewGraphicsInstance( void )
	{
		GraphicsInstance* instance = new GraphicsInstance;
	}

	void GraphicsInstance::Destroy( void )
	{
		CleanupSwapChain();

		// TODO
		//
		//for (auto& dsl : _descriptorSetLayout)
		//	vkDestroyDescriptorSetLayout(_device, dsl, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			vkDestroySemaphore(_device, _renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(_device, _imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(_device, _inFlightFences[i], nullptr);
		}

		vkDestroyCommandPool(_device, _commandPool, nullptr);
		vkDestroyDevice(_device, nullptr);
		if (enableValidationLayers)
			DestroyDebugUtilsMessengerEXT(_vulkanInstance, _debugMessenger, nullptr);
		vkDestroySurfaceKHR(_vulkanInstance, _surface, nullptr);
		vkDestroyInstance(_vulkanInstance, nullptr);
		glfwDestroyWindow(_window);
		//		vkDestroyBuffer(device, vertexBuffer, nullptr);
		//		vkFreeMemory(device, vertexBufferMemory, nullptr);
	}

	void	GraphicsInstance::FramebufferResizeCallback(GLFWwindow *window, int width, int height)
	{
		auto app = reinterpret_cast<GraphicsInstance*>(glfwGetWindowUserPointer(window));
		app->_framebufferResized = true;
		std::cout << width << " " << height << std::endl;
		OS::GetInstance()->SetWindowSizeAttribute(width, height);
	}

	VkSampler GraphicsInstance::CreateTextureSampler( void )
	{
		VkSampler textureSampler;

		VkSamplerCreateInfo samplerInfo = {};
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter = VK_FILTER_LINEAR;
		samplerInfo.minFilter = VK_FILTER_LINEAR;
		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT; // VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.anisotropyEnable = VK_TRUE;
		samplerInfo.maxAnisotropy = 16;
		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

		if (vkCreateSampler(_device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
			throw std::runtime_error("failed to create texture sampler!");

		// TODO
		//     vkDestroySampler(device, textureSampler, nullptr);
		//    vkDestroyImageView(device, textureImageView, nullptr);
		return textureSampler;
	}

//	void GraphicsInstance::CreateTextureImageView( void )
//	{
//		// TODO Cleanup
//		VkImageView	textureImageView;
//		VkImage		textureImage;
//
//		textureImageView = CreateImageView(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
//	}

	ImageRenderer GraphicsInstance::CreateTextureImage( Texture* texture )
	{
		ImageRenderer ir;
		size_t imageSize = texture->_tType * texture->_width * texture->_height * 4;//texture->_format;
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		std::cout << "ImageSize BUFFER CREATION : " << imageSize <<  std::endl;
		std::cout << "width " << texture->_width <<  " " << "Height : " << texture->_height << "Format : " << texture->_format << std::endl;

		CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(_device, stagingBufferMemory, 0, imageSize, 0, &data);
		memcpy(data, texture->_data, static_cast<size_t>(imageSize));
		vkUnmapMemory(_device, stagingBufferMemory);

		CreateImage(texture->_width, texture->_width, texture->_tType, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, ir._textureImage, ir._textureImageMemory);

		TransitionImageLayout(ir._textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, texture->_tType == TextureType::TEXTURE_2D ? VK_IMAGE_VIEW_TYPE_2D : VK_IMAGE_VIEW_TYPE_CUBE);
		CopyBufferToImage(stagingBuffer, ir._textureImage, static_cast<uint32_t>(texture->_width), static_cast<uint32_t>(texture->_height), texture->_tType == TextureType::TEXTURE_2D ? VK_IMAGE_VIEW_TYPE_2D : VK_IMAGE_VIEW_TYPE_CUBE);
		TransitionImageLayout(ir._textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, texture->_tType == TextureType::TEXTURE_2D ? VK_IMAGE_VIEW_TYPE_2D : VK_IMAGE_VIEW_TYPE_CUBE);

		vkDestroyBuffer(_device, stagingBuffer, nullptr);
		vkFreeMemory(_device, stagingBufferMemory, nullptr);

		// TODO
		//	vkDestroyImage(device, textureImage, nullptr);
		//	vkFreeMemory(device, textureImageMemory, nullptr);

		return (ir);
	}

	void GraphicsInstance::CreateImage(uint32_t width, uint32_t height, TextureType tType, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory)
	{
		VkImageCreateInfo imageInfo = {};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = width;
		imageInfo.extent.height = height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		if (tType == TextureType::TEXTURE_CUBE)
		{
			imageInfo.arrayLayers = 6;
			imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
		}
		else
			imageInfo.arrayLayers = 1;

		if (vkCreateImage(_device, &imageInfo, nullptr, &image) != VK_SUCCESS)
			throw std::runtime_error("failed to create image!");

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(_device, image, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(_device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate image memory!");

		vkBindImageMemory(_device, image, imageMemory, 0);
	}

	VkCommandBuffer GraphicsInstance::BeginSingleTimeCommands( void )
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = _commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(_device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}

	void GraphicsInstance::EndSingleTimeCommands(VkCommandBuffer commandBuffer)
	{
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(_graphicsQueue);

		vkFreeCommandBuffers(_device, _commandPool, 1, &commandBuffer);
	}

	void GraphicsInstance::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkImageViewType vType)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

		VkImageMemoryBarrier barrier = {};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = oldLayout;
		barrier.newLayout = newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = image;

		if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

			if (HasStencilComponent(format))
				barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
		else
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = vType == VK_IMAGE_VIEW_TYPE_2D ? 1 : 6;

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		}
		else
		{
			throw std::invalid_argument("unsupported layout transition!");
		}

		vkCmdPipelineBarrier(
				commandBuffer,
				sourceStage, destinationStage,
				0,
				0, nullptr,
				0, nullptr,
				1, &barrier
				);

		EndSingleTimeCommands(commandBuffer);
	}

	void GraphicsInstance::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkImageViewType vType)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

		VkBufferImageCopy region = {};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = vType == VK_IMAGE_VIEW_TYPE_2D ? 1 : 6;
		region.imageOffset = {0, 0, 0};
		region.imageExtent = {
			width,
			height,
			1
		};

		vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

		EndSingleTimeCommands(commandBuffer);
	}

	void GraphicsInstance::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
	{
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(_device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
			throw std::runtime_error("failed to create buffer!");

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(_device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(_device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate buffer memory!");

		vkBindBufferMemory(_device, buffer, bufferMemory, 0);
	}

	BufferRenderer GraphicsInstance::CreateIndexBuffer( std::vector<uint32_t> indexData )
	{
		BufferRenderer bufRenderer;
		VkDeviceSize bufferSize = sizeof(uint32_t) * indexData.size();
		std::cout << "INDEX BUFFER CREATION : " << bufferSize << std::endl;

		bufRenderer._Buffer.resize(1);
		bufRenderer._BufferMemory.resize(1);

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(_device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indexData.data(), (size_t)bufferSize);
		vkUnmapMemory(_device, stagingBufferMemory);

		CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufRenderer._Buffer[0], bufRenderer._BufferMemory[0]);

		CopyBuffer(stagingBuffer, bufRenderer._Buffer[0], bufferSize);

		vkDestroyBuffer(_device, stagingBuffer, nullptr);
		vkFreeMemory(_device, stagingBufferMemory, nullptr);

		return (bufRenderer);
	}

	void GraphicsInstance::CopyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size )
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = _commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(_device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion = {};
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(_graphicsQueue);

		vkFreeCommandBuffers(_device, _commandPool, 1, &commandBuffer);
	}

	std::vector<VkDescriptorSetLayout> GraphicsInstance::CreateDescriptorSetLayout( std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding )
	{
		std::vector<VkDescriptorSetLayout>		descriptorSetLayout;

		VkDescriptorSetLayoutCreateInfo layoutInfo = {};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 1;

		descriptorSetLayout.resize(uboLayoutBinding.size());
		for (int j = 0 ; j < descriptorSetLayout.size() ; j++)
		{
			layoutInfo.pBindings = &uboLayoutBinding[j];
			if (vkCreateDescriptorSetLayout(_device, &layoutInfo, nullptr, &(descriptorSetLayout[j])) != VK_SUCCESS)
				throw std::runtime_error("failed to create descriptor set layout!");
		}
		return (descriptorSetLayout);
	}

	BufferRenderer GraphicsInstance::CreateUniformBuffers( size_t size )
	{
		BufferRenderer buf;
		VkDeviceSize bufferSize = size;
		std::cout << "UNIFORM BUFFER CREATION : " << bufferSize << std::endl;

		buf._Buffer.resize(_swapChainImages.size());
		buf._BufferMemory.resize(_swapChainImages.size());

		for (size_t i = 0; i < _swapChainImages.size(); i++)
			CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buf._Buffer[i], buf._BufferMemory[i]);

		return (buf);
	}

	void GraphicsInstance::CreateDescriptorPool( void )
	{
		VkDescriptorPoolSize poolSize[3] = {};
		poolSize[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize[0].descriptorCount = 50 * static_cast<uint32_t>(_swapChainImages.size());
		poolSize[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSize[1].descriptorCount = 50 * static_cast<uint32_t>(_swapChainImages.size());
		poolSize[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		poolSize[2].descriptorCount = 10 * static_cast<uint32_t>(_swapChainImages.size());

		VkDescriptorPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 3; // number of elements in pPoolSizes.
		poolInfo.pPoolSizes = &poolSize[0];
		poolInfo.maxSets = poolSize[0].descriptorCount + poolSize[1].descriptorCount + poolSize[2].descriptorCount;

		if (vkCreateDescriptorPool(_device, &poolInfo, nullptr, &_descriptorPool) != VK_SUCCESS)
			throw std::runtime_error("failed to create descriptor pool!");
	}

	std::vector<VkDescriptorSet> GraphicsInstance::CreateImageDescriptorSets( VkImageView textureImageView, VkSampler textureSampler, VkDescriptorSetLayout descriptorSetLayout )
	{
		std::vector<VkDescriptorSet> ds;

		std::vector<VkDescriptorSetLayout> layouts(_swapChainImages.size(), descriptorSetLayout);

		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = _descriptorPool;
		allocInfo.descriptorSetCount = 1 * static_cast<uint32_t>(_swapChainImages.size()); // number of descriptor sets to be allocated from the pool.
		allocInfo.pSetLayouts = layouts.data();

		ds.resize(_swapChainImages.size());
		if (vkAllocateDescriptorSets(_device, &allocInfo, ds.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate descriptor sets!");

		for (size_t i = 0; i < _swapChainImages.size(); i++)
		{
			VkDescriptorImageInfo imageInfo = {};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = textureImageView;
			imageInfo.sampler = textureSampler;

			VkWriteDescriptorSet descriptorWrite = {};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = ds[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(_device, 1, &descriptorWrite, 0, nullptr);
		}

		return (ds);
	}

	// TODO : MULTISET DYNAMIC
	std::vector<VkDescriptorSet> GraphicsInstance::CreateDescriptorSets( size_t size, std::vector<VkDescriptorSetLayout> layoutArray, int dlayout, VkBuffer* gpuBuffers, VkDescriptorType dType)
	{
		std::vector<VkDescriptorSet> descriptorSets;
		std::vector<VkDescriptorSetLayout> layouts(_swapChainImages.size(), layoutArray.at(dlayout));

		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = _descriptorPool;
		allocInfo.descriptorSetCount = 1 * static_cast<uint32_t>(_swapChainImages.size()); // number of descriptor sets to be allocated from the pool.
		allocInfo.pSetLayouts = layouts.data();

		descriptorSets.resize(_swapChainImages.size());
		if (vkAllocateDescriptorSets(_device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate descriptor sets!");

		for (size_t i = 0; i < _swapChainImages.size(); i++)
		{
			VkDescriptorBufferInfo bufferInfo = {};
			if (dType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
				bufferInfo.buffer = gpuBuffers[i];
			else if (dType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER)
				bufferInfo.buffer = gpuBuffers[0];
			bufferInfo.offset = 0;
			bufferInfo.range = size;

			VkWriteDescriptorSet descriptorWrite = {};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = descriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = dType;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;

			vkUpdateDescriptorSets(_device, 1, &descriptorWrite, 0, nullptr);
		}

		return (descriptorSets);
	}

	UniformSets GraphicsInstance::CreateUniform( size_t size, std::vector<VkDescriptorSetLayout> layoutArray, int dlayout )
	{
		UniformSets ds;

		ds._uniformRender = CreateUniformBuffers(size);

		ds._descriptorSets = CreateDescriptorSets( size, layoutArray, dlayout, ds._uniformRender._Buffer.data(), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER );

		return (ds);
	}

	///////////// DEPTH BUFFER / STENCIL BUFFER ///////////////

	VkFormat GraphicsInstance::FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
	{
		for (VkFormat format : candidates)
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
				return format;
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
				return format;
		}

		throw std::runtime_error("failed to find supported format!");
	}

	VkFormat GraphicsInstance::FindDepthFormat( void )
	{
		return FindSupportedFormat(
				{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
				VK_IMAGE_TILING_OPTIMAL,
				VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
				);
	}

	bool GraphicsInstance::HasStencilComponent(VkFormat format)
	{
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}

	void GraphicsInstance::CreateDepthResources( void )
	{
		VkFormat depthFormat = FindDepthFormat();

		CreateImage(_swapChainExtent.width, _swapChainExtent.height, TextureType::TEXTURE_2D, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _depthImage, _depthImageMemory);
		_depthImageView = CreateImageView(_depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, VK_IMAGE_VIEW_TYPE_2D);

		TransitionImageLayout(_depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_VIEW_TYPE_2D);
	}

	//////////// GETTER ////////////

	VkDevice GraphicsInstance::GetDevice( void )
	{
		return (_device);
	}

	VkExtent2D GraphicsInstance::GetSwapChainExtent( void )
	{
		return _swapChainExtent;
	}

	VkRenderPass GraphicsInstance::GetRenderPass( void )
	{
		return (_renderPass);
	}
	////////// INIT ////////////

	void GraphicsInstance::Initialize( void )
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
		CreateImageViews();
		CreateRenderPass();

		CreateCommandPool();

		CreateDepthResources();
		CreateFramebuffers(); 
		CreateDescriptorPool();
		CreateSyncObjects();

		CreateCommandBuffers();
	}
}
