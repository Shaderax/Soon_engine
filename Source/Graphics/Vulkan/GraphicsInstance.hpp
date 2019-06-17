#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Core/Math/mat4.hpp"
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include "Scene/Common/Material.hpp"

enum DescriptorTypeLayout
{
	CAMERA = 0,
	MODEL = 1,
	IMAGE = 2,
	MATERIAL = 3,
	LIGHT = 4
};

//Swap chain struct
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex
{
	vec3<float> _position;
	vec3<float> _normal;
	vec2<float> _texCoords;
};

struct BufferRenderer
{
	std::vector<VkBuffer>		_Buffer;
	std::vector<VkDeviceMemory>	_BufferMemory;
};

struct ImageRenderer
{
	VkImage			_textureImage;
	VkDeviceMemory	_textureImageMemory;
};

struct VertexBufferInfo
{
	uint32_t	_nbVertex;
	size_t		_vertexSize;
	void*		_vertexData;
	size_t		_indexSize;
	void*		_indexData;
	Material*	_material;
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

struct UniformMaterial
{
	vec3<float>    _ambient;
	vec3<float>    _diffuse;
	vec3<float>    _specular;
	float   _shininess;
};

struct UniformLight
{
	vec3<float> _direction;
	vec3<float> _lightColor;
	float _intensity;
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
			VkDescriptorPool				_descriptorPool;

			VkImage							_depthImage;
			VkDeviceMemory					_depthImageMemory;
			VkImageView						_depthImageView;

			static GraphicsInstance*		_singleton;

		public:
			static GraphicsInstance* GetInstance( void );
			GraphicsInstance( void );
			~GraphicsInstance( void );
			void Initialize( void );
			void Destroy( void );
			GLFWwindow* GetWindow( void );

			void	CreateInstance( void );
			void	PickPhysicalDevice( void );
			void	CreateLogicalDevice( void );
			void	CreateWindow( void );
			void	CreateSurface( void );
			void	GetPhysicalDeviceInfo( void );
			void	GetPhysicalDeviceInfo(VkPhysicalDevice device);
			int		GetQueueFamilyIndex(VkPhysicalDevice device, VkQueueFlagBits queue);
			int		RateDeviceSuitable(VkPhysicalDevice device);
			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
			void	CreateSwapChain( void );
			void 	SetupDebugMessenger( void );
			void 	CreateImageViews( void );
			VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags );
			void 	CreateGraphicsPipeline( void );
			VkShaderModule CreateShaderModule(const std::vector<char>& code);
			void	CreateRenderPass( void );
			void 	CreateFramebuffers( void );
			void 	CreateCommandPool( void );
			void 	CreateCommandBuffers( void );
			void 	CreateSyncObjects( void );
			void 	DrawFrame( void );
			void 	RecreateSwapChain( void );
			void 	CleanupSwapChain( void );
			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);
			std::vector< BufferRenderer > CreateVertexBuffer( VertexBufferInfo inf );
			uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
			void	FillCommandBuffer( void );
			void 	CreateDescriptorSetLayout( void );
			void 	CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
			BufferRenderer CreateUniformBuffers( size_t size );
			void	UpdateUniformBuffer(uint32_t currentImage);
			void 	CreateDescriptorPool( void );
			UniformSets CreateDescriptorSets( size_t size, DescriptorTypeLayout dlayout);
			std::vector<VkDescriptorSet> CreateImageDescriptorSets( VkImageView textureImageView, VkSampler textureSampler );
			UniformSets CreateUniform( size_t size, DescriptorTypeLayout dlayout );
			ImageRenderer	CreateTextureImage( Texture2D* texture );
			void 	CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
			VkCommandBuffer BeginSingleTimeCommands( void );
			void	EndSingleTimeCommands(VkCommandBuffer commandBuffer);
			void 	TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
			void 	CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
			VkSampler	CreateTextureSampler( void );
			void	CreateTextureImageView( void );
			BufferRenderer CreateIndexBuffer( VertexBufferInfo inf );
			void CopyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size );
			VkFormat FindDepthFormat( void );
			VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
			void CreateDepthResources( void );
			bool HasStencilComponent(VkFormat format);



			void 	NewGraphicsInstance( void );

	};
}
