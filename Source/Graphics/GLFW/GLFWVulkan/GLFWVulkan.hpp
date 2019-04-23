#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Graphics/GraphicsInstance.hpp"
//#include "vulkan/vulkan.h"

namespace Soon
{
	class GLFWVulkan : GraphicsInstance
	{
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

		private:
			GLFWwindow*			_window;
			VkInstance			_vulkanInstance;
			VkPhysicalDevice	_physicalDevice;
			VkDevice 			_device;
			VkQueue				_graphicsQueue;
			VkSurfaceKHR 		_surface;
			VkQueue				_presentQueue;
	};

	void NewGraphicsInstance( void );
}
