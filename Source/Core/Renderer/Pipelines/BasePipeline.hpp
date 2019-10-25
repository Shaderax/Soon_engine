#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

namespace Soon
{
	enum struct PipelineType : uint32_t
	{
		GRAPHIC = 0,
		COMPUTE = 1
	};

	class BasePipeline
	{
		public:
		BasePipeline( void )
		{

		}

		virtual ~BasePipeline() {}
		virtual std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void ) = 0;
		virtual void UpdateData( int currentImg ) = 0;
		virtual void BindCaller( VkCommandBuffer commandBuffer, uint32_t index ) = 0;
//		virtual std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void ) = 0;
//		virtual VkVertexInputBindingDescription GetBindingDescription( void ) = 0;
		virtual void RecreateUniforms( void ) = 0;
		virtual void RecreatePipeline( void ) = 0;

		virtual void RemoveFromPipeline( void ) = 0;
		virtual void Enable( void ) = 0;
		virtual void Disable( void ) = 0;

		std::vector<VkDescriptorSetLayout>		_descriptorSetLayout;
		VkPipelineLayout 						_pipelineLayout;
		VkPipeline								_graphicPipeline;


	};
}
