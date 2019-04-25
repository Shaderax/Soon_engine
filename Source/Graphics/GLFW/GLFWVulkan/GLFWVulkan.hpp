#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Graphics/GraphicsInstance.hpp"
#include <vector>
//#include "vulkan/vulkan.h"

//Swap chain struct
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

namespace Soon
{
	class GLFWVulkan : GraphicsInstance
	{

		private:
			GLFWwindow*			_window;
			VkInstance			_vulkanInstance;
			VkPhysicalDevice	_physicalDevice;
			VkDevice 			_device;
			VkQueue				_graphicsQueue;
			VkSurfaceKHR 		_surface;
			VkQueue				_presentQueue;
			VkSwapchainKHR		_swapChain;
			std::vector<VkImage> _swapChainImages;
			VkExtent2D			_swapChainExtent;
			VkFormat			_swapChainImageFormat;
			VkDebugUtilsMessengerEXT	_debugMessenger;
			std::vector<VkImageView> _swapChainImageViews;
			VkPipelineLayout 		_pipelineLayout;
			VkRenderPass			_renderPass;

		public:
			GLFWVulkan( void );
			~GLFWVulkan( void );
			virtual void Initialize( void );
			virtual void Destroy( void );
			virtual void* GetContext( void );

			void CreateInstance( void );
			void PickPhysicalDevice( void );
			void CreateLogicalDevice( void );
			void CreateWindow( void );
			void CreateSurface( void );

			void GetPhysicalDeviceInfo( void );
			void GetPhysicalDeviceInfo(VkPhysicalDevice device);

			int GetQueueFamilyIndex(VkPhysicalDevice device, VkQueueFlagBits queue);
			int RateDeviceSuitable(VkPhysicalDevice device);

			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

			void CreateSwapChain( void );

			void SetupDebugMessenger( void );

			void CreateImageViews( void );

			void CreateGraphicsPipeline( void );

			VkShaderModule CreateShaderModule(const std::vector<char>& code);

			void CreateRenderPass( void );
	};

	void NewGraphicsInstance( void );
}
