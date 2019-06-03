#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "Core/Math/mat4.hpp"

//Swap chain struct
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct BufferRenderer
{
	std::vector<VkBuffer>		_Buffer;
	std::vector<VkDeviceMemory>	_BufferMemory;
};

struct VertexBufferInfo
{
	uint32_t	_nbVertex;
	size_t		_size;
	void*		_data;
};

struct UniformCamera
{
	mat4<float> view;
	mat4<float> proj;
};

struct UniformModel
{
	mat4<float> model;
};

struct UniformSets
{
	std::vector<VkDescriptorSet>	_descriptorSets;
	BufferRenderer					_uniformRender;
};

namespace Soon
{
	class GraphicsInstance
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
			std::vector<VkDescriptorSetLayout>			_descriptorSetLayout;
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
			//			VkBuffer						_vertexBuffer;
			//			VkDeviceMemory					_vertexBufferMemory;

//			std::vector<VkBuffer>			_uniformBuffers;
//			std::vector<VkDeviceMemory>		_uniformBuffersMemory;
			VkDescriptorPool				_descriptorPool;
//			std::vector<VkDescriptorSet>	_descriptorSets;

			static GraphicsInstance*		_singleton;

		public:
			static GraphicsInstance* GetInstance( void );
			GraphicsInstance( void );
			~GraphicsInstance( void );
			void Initialize( void );
			void Destroy( void );
			GLFWwindow* GetWindow( void );

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

			void FillCommandBuffer( void );

			void CreateDescriptorSetLayout( void );

			void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

			BufferRenderer CreateUniformBuffers( size_t size );

			void UpdateUniformBuffer(uint32_t currentImage);

			void CreateDescriptorPool( void );

			UniformSets CreateDescriptorSets( size_t size );

			UniformSets CreateUniform( size_t size);
	};

	void NewGraphicsInstance( void );
}
