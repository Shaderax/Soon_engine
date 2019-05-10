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

struct BufferRenderer
{
	VkBuffer                        _vertexBuffer;
	VkDeviceMemory                  _vertexBufferMemory;
};

struct VertexBufferInfo
{
	size_t	_nbVertex;
	size_t	_size;
	void*	_data;
};

namespace Soon
{
	class GLFWVulkan : GraphicsInstance
	{
		private:
			GLFWwindow*						_window;
			VkInstance						_vulkanInstance;
			VkPhysicalDevice				_physicalDevice;
			VkDevice 						_device;
			VkQueue							_graphicsQueue;
			VkSurfaceKHR 					_surface;
			VkQueue							_presentQueue;
			VkSwapchainKHR					_swapChain;
			std::vector<VkImage>			_swapChainImages;
			VkExtent2D						_swapChainExtent;
			VkFormat						_swapChainImageFormat;
			VkDebugUtilsMessengerEXT		_debugMessenger;
			std::vector<VkImageView>		_swapChainImageViews;
			VkPipelineLayout 				_pipelineLayout;
			VkPipeline						_graphicsPipeline;
			VkRenderPass					_renderPass;
			std::vector<VkFramebuffer> 		_swapChainFramebuffers;
			VkCommandPool 					_commandPool;
			std::vector<VkCommandBuffer>	_commandBuffers;
			std::vector<VkSemaphore>		_imageAvailableSemaphores;
			std::vector<VkSemaphore>		_renderFinishedSemaphores;
			std::vector<VkFence>			_inFlightFences;
			size_t							_currentFrame;
			bool 							_framebufferResized;
			VkBuffer						_vertexBuffer;
			VkDeviceMemory					_vertexBufferMemory;

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

			void CreateFramebuffers( void );

			void CreateCommandPool( void );

			void CreateCommandBuffers( void );

			void CreateSyncObjects( void );

			void DrawFrame( void );

			void RecreateSwapChain( void );

			void CleanupSwapChain( void );

			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

			static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);

			BufferRenderer CreateVertexBuffer( VertexBufferInfo inf );

			uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

			void RecreateCommandBuffer( void );
	};

	void NewGraphicsInstance( void );
}
